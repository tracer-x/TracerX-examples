#!/usr/bin/env bash
#
# Additional LLBMC experiments requested by Roland Yap May 2017.
# Here we vary the loop iteration bounds and see if LLBMC manages
# to discover more errors. The result is that all runs discover
# the same error (LLBMC terminates after the first error).
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COREUTILS_DIR=$SCRIPT_DIR/../coreutils

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

cd $COREUTILS_DIR

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/cut.llbmc102
export LLBMC_OPTIONS=--ignore-missing-function-bodies -function-name=main -max-loop-iterations=5 -max-function-call-depth=10
# Following is the KLEE options substituted
#export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 5 --sym-stdout"
#export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 6 --sym-stdout"
#export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 7 --sym-stdout"
export PROGRAM_OPTIONS="-b xxx"
make cut.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/cut.llbmc103
export LLBMC_OPTIONS=--ignore-missing-function-bodies -function-name=main -max-loop-iterations=6 -max-function-call-depth=10
export PROGRAM_OPTIONS="-b xxx"
make cut.llbmc

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/cut.llbmc104
export LLBMC_OPTIONS=--ignore-missing-function-bodies -function-name=main -max-loop-iterations=7 -max-function-call-depth=10
export PROGRAM_OPTIONS="-b xxx"
make cut.llbmc

cd $SCRIPT_DIR
