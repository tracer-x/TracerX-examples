# Makefile to build and run the examples using KLEE.
#
# Copyright 2015, 2016 National University of Singapore

# We enable execution tree (tree.dot) output as the examples
# in this directory are small.
EXTRA_OPTIONS=-output-tree -interpolation-stat -write-pcs -use-query-log=all:pc,all:smt2

# This is for the options passed onto the tested program, e.g.,
# --sym-arg
PROGRAM_OPTIONS=

TARGETS=$(patsubst %.c,%.klee,$(wildcard *c))

include ../Makefile.common

clean: standard-clean

