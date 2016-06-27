# Makefile to build and run the examples using KLEE.
#
# Copyright 2015 National University of Singapore

# We enable execution tree (tree.dot) output as the examples
# in this directory are small.
EXTRA_OPTIONS=-output-tree -interpolation-stat -write-pcs -use-query-log=all:pc,all:smt2

TARGETS=$(patsubst %.c,%.klee,$(wildcard *c))

include ../Makefile.common

clean: standard-clean

