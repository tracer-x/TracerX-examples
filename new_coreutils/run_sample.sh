#!/bin/bash
if [[ $# -lt 2 ]] ; then
    echo 'Usage: ./run_sample.sh tracerx_bin_folder coreutils_folder'
    exit 0
fi

if [ ! -d "/tmp/sandbox" ]; then
    echo "|  SET UP SANDBOX  |"
    wget https://www.doc.ic.ac.uk/~cristic/klee/testing-env.sh
    env -i /bin/bash -c '(source testing-env.sh; env >test.env)'
    wget -O - https://www.doc.ic.ac.uk/~cristic/klee/sandbox.tgz | tar -xvzf - -C /tmp
    echo "|  FINISH SET UP SANDBOX  |"
fi

TRACERX_BIN=$1
COREUTILS_BC=$2/obj-llvm/src
OUTPUT_FOLDER=`pwd`/sample_result
COMMON_OPTIONS="--libc=uclibc --posix-runtime --environ=test.env --run-in=/tmp/sandbox \
    -only-output-states-covering-new --disable-inlining --use-forked-solver \
    --use-cex-cache --allow-external-sym-calls --max-sym-array-size=4096 \
    --max-instruction-time=30 --watchdog --max-memory-inhibit=false \
    --max-static-fork-pct=1 --max-static-solve-pct=1 --max-static-cpfork-pct=1 \
    --switch-type=internal --randomize-fork --use-batching-search --batch-instructions=10000 \
    --max-memory=32000 --max-time=3600 -no-output --optimize --simplify-sym-indices -write-BB-cov=1"

# running experiments
DEFAUL_SYM_OPTIONS='--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout'
declare -A BENCHMARKS
BENCHMARKS=(
    [echo]='--sym-arg 3' \
    # [echo]='--sym-args 0 4 300 --sym-files 2 30 --sym-stdout' \
    # [pwd]= \
    # [sync]= \
    # [basename]= \
    # [dirname]= \
    # [users]= \
    # [uptime]= \
    # [chroot]= \
    # [cksum]= \
    # [runcon]= \
    # [hostname]= \
    # [printenv]= \
    # [who]= \
    # [nice]= \
    # [pinky]= \
    # [shred]= \
    # [tty]= \
    # [fold]= \
    # [rmdir]= \
    # [nl]= \
    # [setuidgid]= \
    # [sleep]= \
    # [chcon]= \
    # [head]= \
    # [hostid]= \
    # [ln]= \
    # [logname]= \
    # [mkdir]= \
    # [mkfifo]= \


    # [base64]= \
    # [cat]= \
    # [chgrp]= \
    # [comm]= \
    # [df]= \
    # [dircolors]='--sym-args 0 3 10 --sym-files 2 12 --sym-stdout' \
    # [env]='--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8' \
    # [mknod]='--sym-args 0 1 10 --sym-args 0 3 2 --sym-files 1 8 --sym-stdout' \
    # [mktemp]= \
    # [nohup]= \
    # [paste]= \
    # [pr]= \
    # [printf]='--sym-args 0 3 10 --sym-files 2 12 --sym-stdout' \
    # [readlink]= \
    # [rm]= \
    # [tee]= \
    # [unlink]= \
    # [whoami]= \
)

if [ ! -d $OUTPUT_FOLDER ]; then
    mkdir $OUTPUT_FOLDER
fi


TX_RANDOM_OPTIONS="$COMMON_OPTIONS -solver-backend=z3 --search=random-path --search=nurs:covnew -max-subsumption-failure=3"
TX_DFS_OPTIONS="$COMMON_OPTIONS -solver-backend=z3 --search=dfs -max-subsumption-failure=3"
KLEE_RANDOM_OPTIONS="$COMMON_OPTIONS --search=random-path --search=nurs:covnew"

for k in "${!BENCHMARKS[@]}"
do
    # TX_RANDOM
    if [ ! -d $OUTPUT_FOLDER/$k.tx_rand ]; then
        if [[ ${BENCHMARKS[$k]} == "" ]]; then
            $TRACERX_BIN/klee $TX_RANDOM_OPTIONS --output-dir=$OUTPUT_FOLDER/$k.tx_rand $COREUTILS_BC/$k.bc $DEFAUL_SYM_OPTIONS \
            &> $OUTPUT_FOLDER/$k.tx_rand.txt
        else
            $TRACERX_BIN/klee $TX_RANDOM_OPTIONS --output-dir=$OUTPUT_FOLDER/$k.tx_rand $COREUTILS_BC/$k.bc ${BENCHMARKS[$k]} \
            &> $OUTPUT_FOLDER/$k.tx_rand.txt
        fi
        $TRACERX_BIN/klee-stats $OUTPUT_FOLDER/$k.tx_rand >> $OUTPUT_FOLDER/$k.tx_rand/info
        echo "Finish ${k}.tx_rand"
    fi

    # TX_DFS
    if [ ! -d $OUTPUT_FOLDER/$k.tx_dfs ]; then
        if [[ ${BENCHMARKS[$k]} == "" ]]; then
            $TRACERX_BIN/klee $TX_DFS_OPTIONS --output-dir=$OUTPUT_FOLDER/$k.tx_dfs $COREUTILS_BC/$k.bc $DEFAUL_SYM_OPTIONS \
            &> $OUTPUT_FOLDER/$k.tx_dfs.txt
        else
            $TRACERX_BIN/klee $TX_DFS_OPTIONS --output-dir=$OUTPUT_FOLDER/$k.tx_dfs $COREUTILS_BC/$k.bc ${BENCHMARKS[$k]} \
            &> $OUTPUT_FOLDER/$k.tx_dfs.txt
        fi
        $TRACERX_BIN/klee-stats $OUTPUT_FOLDER/$k.tx_dfs >> $OUTPUT_FOLDER/$k.tx_dfs/info
        echo "Finish ${k}.tx_dfs"
    fi

    # KLEE_RANDOM
    if [ ! -d $OUTPUT_FOLDER/$k.klee_rand ]; then
        if [[ ${BENCHMARKS[$k]} == "" ]]; then
            $TRACERX_BIN/klee $KLEE_RANDOM_OPTIONS --output-dir=$OUTPUT_FOLDER/$k.klee_rand $COREUTILS_BC/$k.bc $DEFAUL_SYM_OPTIONS \
            &> $OUTPUT_FOLDER/$k.klee_rand.txt
        else
            $TRACERX_BIN/klee $KLEE_RANDOM_OPTIONS --output-dir=$OUTPUT_FOLDER/$k.klee_rand $COREUTILS_BC/$k.bc ${BENCHMARKS[$k]} \
            &> $OUTPUT_FOLDER/$k.klee_rand.txt
        fi
        $TRACERX_BIN/klee-stats $OUTPUT_FOLDER/$k.klee_rand >> $OUTPUT_FOLDER/$k.klee_rand/info
        echo "Finish ${k}.klee_rand"
    fi
done

# collect experiment result from output folder
python collect_data.py $OUTPUT_FOLDER
