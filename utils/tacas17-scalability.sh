#!/usr/bin/env bash
#
# Scalability experiments for TACAS '18 submission.
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SCALABILITY_DIR=$SCRIPT_DIR/../scalability

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

export EXPERIMENT_SET="malloc9 malloc18 malloc27 motivating1 motivating2 motivating3 Regexp-7-4 Regexp-7-5 Regexp-7-6 insertsort7 insertsort9 insertsort11 bubble_assert3 bubble_assert6 bubble_assert9 nsichneu statemate"
export EXPERIMENT_TYPE_SET=".klee1 .tx1"

( \
    cd $SCALABILITY_DIR ; \
    make experiment.csv ; \
    make llbmc-experiment.csv ; \
)
