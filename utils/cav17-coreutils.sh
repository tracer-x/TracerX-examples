#!/usr/bin/env bash
# Coreutils experiments for CAV '17 submission
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SCALABILITY_DIR=$SCRIPT_DIR/../coreutils

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

cd $COREUTILS_DIR
export KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths"
export OUTPUT_DIR=${CURDIR}/pr.klee101
export PROGRAM_OPTIONS="-a -sym-stdin 4 --sym-stdout"
make pr.klee
export OUTPUT_DIR=${CURDIR}/pr.klee102
export PROGRAM_OPTIONS="-a -sym-stdin 5 --sym-stdout"
make pr.klee
export OUTPUT_DIR=${CURDIR}/pr.klee103
export PROGRAM_OPTIONS="-a -sym-stdin 6 --sym-stdout"
make pr.klee
export OUTPUT_DIR=${CURDIR}/pr.tx101
export PROGRAM_OPTIONS="-a -sym-stdin 4 --sym-stdout"
make pr.tx
export OUTPUT_DIR=${CURDIR}/pr.tx102
export PROGRAM_OPTIONS="-a -sym-stdin 5 --sym-stdout"
make pr.tx
export OUTPUT_DIR=${CURDIR}/pr.tx103
export PROGRAM_OPTIONS="-a -sym-stdin 6 --sym-stdout"
make pr.tx 
export OUTPUT_DIR=${CURDIR}/cut.klee101
export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 4 --sym-stdout"
make cut.klee
export OUTPUT_DIR=${CURDIR}/cut.klee102
export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 5 --sym-stdout"
make cut.klee
export OUTPUT_DIR=${CURDIR}/cut.klee103
export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 6 --sym-stdout"
make cut.klee
export OUTPUT_DIR=${CURDIR}/cut.klee104
export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 7 --sym-stdout"
make cut.klee
export OUTPUT_DIR=${CURDIR}/cut.tx101
export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 4 --sym-stdout"
make cut.tx
export OUTPUT_DIR=${CURDIR}/cut.tx102
export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 5 --sym-stdout"
make cut.tx
export OUTPUT_DIR=${CURDIR}/cut.tx103
export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 6 --sym-stdout"
make cut.tx
export OUTPUT_DIR=${CURDIR}/cut.tx104
export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 7 --sym-stdout"
make cut.tx
export OUTPUT_DIR=${CURDIR}/printf.klee101
export PROGRAM_OPTIONS="-sym-arg 1 -sym-arg 1 --sym-stdout"
make printf.klee
export OUTPUT_DIR=${CURDIR}/printf.klee102
export PROGRAM_OPTIONS="-sym-arg 2 -sym-arg 1 --sym-stdout"
make printf.klee
export OUTPUT_DIR=${CURDIR}/printf.klee103
export PROGRAM_OPTIONS="-sym-arg 3 -sym-arg 1 --sym-stdout"
make printf.klee
export OUTPUT_DIR=${CURDIR}/printf.tx101
export PROGRAM_OPTIONS="-sym-arg 1 -sym-arg 1 --sym-stdout"
make printf.tx
export OUTPUT_DIR=${CURDIR}/printf.tx102
export PROGRAM_OPTIONS="-sym-arg 2 -sym-arg 1 --sym-stdout"
make printf.tx
export OUTPUT_DIR=${CURDIR}/printf.tx103
export PROGRAM_OPTIONS="-sym-arg 3 -sym-arg 1 --sym-stdout"
make printf.tx
export OUTPUT_DIR=${CURDIR}/basename.klee101
export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
make basename.klee
export OUTPUT_DIR=${CURDIR}/basename.klee102
export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 3 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
make basename.klee
export OUTPUT_DIR=${CURDIR}/basename.klee103
export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 4 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
make basename.klee
export OUTPUT_DIR=${CURDIR}/basename.klee104
export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 5 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
make basename.klee
export OUTPUT_DIR=${CURDIR}/basename.tx101
export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
make basename.tx
export OUTPUT_DIR=${CURDIR}/basename.tx102
export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 3 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
make basename.tx
export OUTPUT_DIR=${CURDIR}/basename.tx103
export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 4 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
make basename.tx
export OUTPUT_DIR=${CURDIR}/basename.tx104
export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 5 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
make basename.tx
export OUTPUT_DIR=${CURDIR}/head.klee101
export PROGRAM_OPTIONS="-sym-arg 2 -sym-stdin 8 --sym-stdout"
make head.klee
export OUTPUT_DIR=${CURDIR}/head.klee102
export PROGRAM_OPTIONS="-sym-arg 3 -sym-stdin 8 --sym-stdout"
make head.klee
export OUTPUT_DIR=${CURDIR}/head.klee103
export PROGRAM_OPTIONS="-sym-arg 4 -sym-stdin 8 --sym-stdout"
make head.klee
export OUTPUT_DIR=${CURDIR}/head.tx101
export PROGRAM_OPTIONS="-sym-arg 2 -sym-stdin 8 --sym-stdout"
make head.tx
export OUTPUT_DIR=${CURDIR}/head.tx102
export PROGRAM_OPTIONS="-sym-arg 3 -sym-stdin 8 --sym-stdout"
make head.tx
export OUTPUT_DIR=${CURDIR}/head.tx103
export PROGRAM_OPTIONS="-sym-arg 4 -sym-stdin 8 --sym-stdout"
make head.tx
export OUTPUT_DIR=${CURDIR}/pathchk.klee101
export PROGRAM_OPTIONS="-sym-arg 13 --sym-stdout"
make pathchk.klee
export OUTPUT_DIR=${CURDIR}/pathchk.klee102
export PROGRAM_OPTIONS="-sym-arg 14 --sym-stdout"
make pathchk.klee
export OUTPUT_DIR=${CURDIR}/pathchk.klee103
export PROGRAM_OPTIONS="-sym-arg 15 --sym-stdout"
make pathchk.klee
export OUTPUT_DIR=${CURDIR}/pathchk.klee104
export PROGRAM_OPTIONS="-sym-arg 16 --sym-stdout"
make pathchk.klee
export OUTPUT_DIR=${CURDIR}/pathchk.klee105
export PROGRAM_OPTIONS="-sym-arg 17 --sym-stdout"
make pathchk.klee
export OUTPUT_DIR=${CURDIR}/pathchk.klee106
export PROGRAM_OPTIONS="-sym-arg 18 --sym-stdout"
make pathchk.klee
export OUTPUT_DIR=${CURDIR}/pathchk.tx101
export PROGRAM_OPTIONS="-sym-arg 13 --sym-stdout"
make pathchk.tx
export OUTPUT_DIR=${CURDIR}/pathchk.tx102
export PROGRAM_OPTIONS="-sym-arg 14 --sym-stdout"
make pathchk.tx
export OUTPUT_DIR=${CURDIR}/pathchk.tx103
export PROGRAM_OPTIONS="-sym-arg 15 --sym-stdout"
make pathchk.tx
export OUTPUT_DIR=${CURDIR}/pathchk.tx104
export PROGRAM_OPTIONS="-sym-arg 16 --sym-stdout"
make pathchk.tx
export OUTPUT_DIR=${CURDIR}/pathchk.tx105
export PROGRAM_OPTIONS="-sym-arg 17 --sym-stdout"
make pathchk.tx
export OUTPUT_DIR=${CURDIR}/pathchk.tx106
export PROGRAM_OPTIONS="-sym-arg 18 --sym-stdout"
make pathchk.tx
export EXPERIMENT_SET="pr cut printf basename head pathchk"
export EXPERIMENT_TYPE_SET=".klee101 .klee102 .klee103 .klee104 .klee105 .klee106 .tx101 .tx102 .tx103 .tx104 .tx105 .tx106"
make experiment.csv.only
mv -f experiment.csv.only experiment.csv

cd $SCRIPT_DIR
