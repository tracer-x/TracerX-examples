#!/usr/bin/env bash
# Scalability experiments for FMCAD '17 submission
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SCALABILITY_DIR=$SCRIPT_DIR/../scalability

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

( \
    cd $SCALABILITY_DIR ; \
    export EXPERIMENT_SET="malloc9 malloc18 malloc27 insertsort5 insertsort7 insertsort9 insertsort11 insertsort_assert5 insertsort_assert7 insertsort_assert9 insertsort_assert11 bubble3 bubble4 bubble5 bubble6 bubble7 bubble8 bubble9 bubble12 bubble_assert3 bubble_assert4 bubble_assert5 bubble_assert6 bubble_assert7 bubble_assert8 bubble_assert9 bubble_assert12 Regexp-6-3 Regexp-6-4 Regexp-6-5 Regexp-7-3 Regexp-7-4 Regexp-7-5 Regexp-7-6 Regexp-8-3 Regexp-8-4 Regexp-8-5 nsichneu statemate" ; \
    export EXPERIMENT_TYPE_SET=".klee1 .tx1 .tx2a" ; \
    make experiment.csv ; \
    make llbmc-experiment.csv ; \
)
