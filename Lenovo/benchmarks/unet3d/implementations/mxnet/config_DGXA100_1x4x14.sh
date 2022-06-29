#source $(dirname ${BASH_SOURCE[0]})/config_DGXA100_common.sh

## DL params
export OPTIMIZER="nag"
export BATCH_SIZE="14"
export VAL_BATCH_SIZE="4"
export LR="2.0"
export LR_WARMUP_EPOCHS="1000"
export MAX_EPOCHS=${MAX_EPOCHS:-10000}
export START_EVAL_AT=1000
export EVALUATE_EVERY=${EVALUATE_EVERY:-20}
export QUALITY_THRESHOLD="0.908"
export INPUT_BATCH_MULTIPLIER=4
export NUM_WORKERS=4
export EXTRA_PARAMS=${EXTRA_PARAMS:-""}
export PRECISION=${PRECISION:-"--static_cast -sls 32784 -gpf 4"}

#export SBATCH_NETWORK=sharp
export OMP_NUM_THREADS=1
export HOROVOD_CYCLE_TIME=0.1
#export MXNET_HOROVOD_NUM_GROUPS=20
export OMPI_MCA_btl=^openib
#export NCCL_MAX_RINGS=8
#export NCCL_BUFFSIZE=2097152
#export NCCL_NET_GDR_READ=1
#export HOROVOD_FUSION_THRESHOLD=67108864
#export HOROVOD_NUM_NCCL_STREAMS=1
#export HOROVOD_BATCH_D2D_MEMCOPIES=1
#export HOROVOD_GROUPED_ALLREDUCES=1

## System run parms
export DGXNNODES=1
export DGXSYSTEM=$(basename $(readlink -f ${BASH_SOURCE[0]}) | sed 's/^config_//' | sed 's/\.sh$//' )
WALLTIME_MINUTES=120
#export WALLTIME=$((${NEXP} * ${WALLTIME_MINUTES}))

## System config params
export DGXNGPU=4
export DGXSOCKETCORES=36
export DGXNSOCKET=2
export DGXHT=2  # HT is on is 2, HT off is 1

#source $(dirname ${BASH_SOURCE[0]})/config_DGXA100_common.sh
export NCCL_SOCKET_IFNAME=
