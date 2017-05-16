#!/usr/bin/env bash
# Coreutils experiments for FMCAD '17 submission
#
# Here we only run LLBMC to add LLBMC numbers to CAV '17 KLEE and
# Tracer-X numbers.
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COREUTILS_DIR=$SCRIPT_DIR/../coreutils

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

cd $COREUTILS_DIR

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/cut.llbmc102
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 5 --sym-stdout"
#export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 6 --sym-stdout"
#export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 7 --sym-stdout"
export PROGRAM_OPTIONS="-b xxx"
make cut.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/basename.llbmc102
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 3 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxx xxx xxx"
make basename.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/basename.llbmc103
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 4 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxx xxxx xxxx"
make basename.llbmc

rm -f llbmc-experiment.csv.only
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/basename.llbmc104
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 5 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxx xxxxx xxxxx"
make basename.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc101
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="-sym-arg 13 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxxxxx"
make pathchk.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc102
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="-sym-arg 14 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxxxxxx"
make pathchk.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc103
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="-sym-arg 15 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxxxxxxx"
make pathchk.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc104
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="-sym-arg 16 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxxxxxxxx"
make pathchk.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc105
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="-sym-arg 17 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxxxxxxxxx"
make pathchk.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc106
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="-sym-arg 18 --sym-stdout"
export PROGRAM_OPTIONS="xxxxxxxxxxxxxxxxxx"
make pathchk.llbmc

export OUTPUT_DIR_SET="$COREUTILS_DIR/cut.llbmc102 $COREUTILS_DIR/basename.llbmc102 $COREUTILS_DIR/basename.llbmc103 $COREUTILS_DIR/basename.llbmc104 $COREUTILS_DIR/pathchk.llbmc101 $COREUTILS_DIR/pathchk.llbmc102 $COREUTILS_DIR/pathchk.llbmc103 $COREUTILS_DIR/pathchk.llbmc104 $COREUTILS_DIR/pathchk.llbmc105 $COREUTILS_DIR/pathchk.llbmc106"
make llbmc-experiment.csv.only
	      
cd $SCRIPT_DIR
