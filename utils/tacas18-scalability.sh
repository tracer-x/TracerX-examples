#!/usr/bin/env bash
#
# Scalability experiments for TACAS '18 submission.
# The result for scalability experiment for statemate-old.c
# wlll be in scalability/LLBMC_STATEMATE_OLD directory.
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SCALABILITY_DIR=$SCRIPT_DIR/../scalability

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

export EXPERIMENT_SET="malloc9 malloc18 malloc27 motivating2 motivating3 motivating4 Regexp-7-5 Regexp-7-6 Regexp-7-7 insertsort7 insertsort9 insertsort11 bubble_assert3 bubble_assert6 bubble_assert9 nsichneu statemate-old"
export EXPERIMENT_TYPE_SET=".klee1 .tx1"

( \
    cd $SCALABILITY_DIR ; \
    make clean ; \
    make experiment.csv ; \
    make llbmc-experiment.csv ; \
    LLBMC_OUTPUT_DIR=$SCALABILITY_DIR/LLBMC_STATEMATE_OLD \
    LLBMC_OPTIONS="--ignore-missing-function-bodies -function-name=main --no-max-loop-iterations-checks --no-max-function-call-depth-checks -max-loop-iterations=60 -max-function-call-depth=10" \
    make statemate-old.llbmc
)
