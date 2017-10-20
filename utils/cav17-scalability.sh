#!/usr/bin/env bash
# Scalability experiments for CAV '17 submission
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SCALABILITY_DIR=$SCRIPT_DIR/../scalability

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

( \
    cd $SCALABILITY_DIR ; \
    export EXPERIMENT_SET="bubble_assert3 bubble_assert6 bubble_assert9 bubble_assert12 Regexp-7-3 Regexp-7-4 Regexp-7-5 Regexp-7-6 insertsort5 insertsort7 insertsort9 insertsort11 statemate-hard nsichneu" ; \
    export EXPERIMENT_TYPE_SET=".klee1 .tx1" ; \
    make experiment.csv ; \
)

