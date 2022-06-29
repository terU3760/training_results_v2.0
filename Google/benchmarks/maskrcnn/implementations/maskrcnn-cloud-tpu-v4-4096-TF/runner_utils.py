# Copyright 2018 Google. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================
"""Util functions for running Mask RCNN model using TPU low level APIs.
"""

import threading
import tensorflow.compat.v1 as tf
from contrib import cluster_resolver as contrib_cluster_resolver
from contrib import framework as contrib_framework


def wrap_computation_in_while_loop(op_fn, n, parallel_iterations=1,
                                   host_name=None):
  """Wraps the ops generated by `op_fn` in tf.while_loop."""

  def computation(i):
    ops = op_fn()
    if not isinstance(ops, list):
      ops = [ops]
    with tf.control_dependencies(ops):
      return i + 1

  if host_name:
    with tf.device(device_for_host(host_name)):
      return tf.while_loop(
          lambda i: tf.less(i, n),
          computation, [tf.constant(0)],
          parallel_iterations=parallel_iterations)
  else:
    return tf.while_loop(
        lambda i: tf.less(i, n),
        computation, [tf.constant(0)],
        parallel_iterations=parallel_iterations)


def device_for_host(host_name):
  return host_name + '/device:CPU:0'


def device_for_tpu_core(host_name, core=0):
  return host_name + '/device:TPU_REPLICATED_CORE:%d' % core


def tpu_ordinal_fn(shard_index_in_host, replicas_per_worker):
  """Return the TPU ordinal associated with a shard."""
  return shard_index_in_host % replicas_per_worker


class InputsFlattener(object):
  """Restores the flattened inputs to original features and labels form.

  Args:
    flattened_inputs: Flattened inputs for each shard.

  Returns:
    A tuple of (`features`, `labels`), where `labels` could be None.
  """

  def __init__(self):
    self._feature_structure = {}

  def flatten_features_and_labels(self, features, labels):
    """Flattens the `features` and `labels` to a single tensor list."""
    self._feature_structure['features'] = features
    if labels is not None:
      self._feature_structure['labels'] = labels
    return contrib_framework.nest.flatten(self._feature_structure)

  def unflatten_features_and_labels(self, flattened_inputs):
    unflattened_inputs = contrib_framework.nest.pack_sequence_as(
        self._feature_structure, flattened_inputs)
    return unflattened_inputs['features'], unflattened_inputs.get('labels')


class InputDimsFlattener(object):
  """"Flatten input_partition_dims for spatial partition."""

  def __init__(self, input_partition_dims):
    self._initialized = False
    self._flattened_input_dims = None

    # This should have been validated in TPUConfig.
    assert len(input_partition_dims) <= 2, 'must have 1 or 2 elements.'
    if len(input_partition_dims) == 2:
      self._feature_dims, self._label_dims = input_partition_dims
    else:
      self._feature_dims = input_partition_dims[0]
      self._label_dims = None

    assert self._feature_dims is not None, ('input_partition_dims[0] must not '
                                            'be None')

  @property
  def flattened_input_dims(self):
    assert self._initialized, 'InputsStructureRecorder is not initialized.'
    return self._flattened_input_dims

  def validate_and_flatten_input_dims(self, features, labels):
    """Flatten input dims with the same order as flattened input tensors."""
    def _extract_key_names(tensor_or_dict):
      if isinstance(tensor_or_dict, dict):
        return sorted(tensor_or_dict.keys())
      return []

    if self._initialized:
      return self._flattened_input_dims

    has_labels = labels is not None
    feature_names = _extract_key_names(features)
    label_names = _extract_key_names(labels)
    feature_dims_names = _extract_key_names(self._feature_dims)
    if feature_dims_names != feature_names:
      raise ValueError(
          'TPUConfig.input_partition_dims[0] mismatched feature'
          ' keys. Expected {}, got {}'.format(feature_names,
                                              feature_dims_names))

    label_dims_names = _extract_key_names(self._label_dims)
    if self._label_dims is not None and label_dims_names != label_names:
      raise ValueError(
          'TPUConfig.input_partition_dims[1] mismatched label'
          ' keys. Expected {}, got {}'.format(label_names,
                                              label_dims_names))

    flattened_input_dims = []
    if feature_dims_names:
      # We need a fixed ordering for matching the tensors in features.
      flattened_input_dims.extend(
          [self._feature_dims[name] for name in feature_dims_names])
    else:
      flattened_input_dims.append(self._feature_dims)

    if label_dims_names:
      # We need a fixed ordering for matching the tensors in labels.
      flattened_input_dims.extend(
          [self._label_dims[name] for name in label_dims_names])
    else:
      if label_names:
        num_tensors_in_label = len(label_names)
      else:
        num_tensors_in_label = int(has_labels)
      # Setting `None` in input_partition_dims[1] will apply `None` to
      # all the tensors in labels, regardless of internal structure.
      flattened_input_dims.extend([self._label_dims] * num_tensors_in_label)

    self._flattened_input_dims = flattened_input_dims
    self._initialized = True


def create_tpu_cluster_resolver(use_tpu, tpu, tpu_zone, gcp_project):
  """Create a new TPUClusterResolver."""
  if use_tpu:
    tpu_cluster_resolver = contrib_cluster_resolver.TPUClusterResolver(
        tpu, zone=tpu_zone, project=gcp_project)
  else:
    tpu_cluster_resolver = None
  return tpu_cluster_resolver


class AsyncCheckpointSaver(object):
  """Save model checkpoint in async threads."""

  def __init__(self, num_checkpoint_threads, saver, model_dir, sess):
    self.thread_id = 0
    self.num_threads = num_checkpoint_threads
    self.checkpoint_threads = [None] * num_checkpoint_threads
    self.model_dir = model_dir
    self.sess = sess
    self.saver = saver

  def __del__(self):
    for i in range(self.num_threads):
      if self.checkpoint_threads[i] is not None:
        self.checkpoint_threads[i].join()
        self.checkpoint_threads[i] = None

  def checkpoint(self, cur_step):
    """Save model checkpoint in async threads."""
    def checkpoint_thread_fn(saver, sess, save_path):
      saver.save(sess, save_path)
    save_path = self.model_dir + '/model.ckpt-%d' % cur_step
    tf.logging.info(
        'saving checkpoints for %d into %s' % (cur_step, save_path))
    if self.checkpoint_threads[self.thread_id] is not None:
      self.checkpoint_threads[self.thread_id].join()
    self.checkpoint_threads[self.thread_id] = threading.Thread(
        target=checkpoint_thread_fn,
        args=(self.saver, self.sess, save_path))
    self.checkpoint_threads[self.thread_id].start()
    self.thread_id += 1
    if self.thread_id >= self.num_threads:
      self.thread_id = 0
