# Makefile to build and run the examples using KLEE.
#
# Copyright 2015-2017 National University of Singapore

# We enable execution tree (tree.dot) output as the examples
# in this directory are small.
EXTRA_OPTIONS=-output-tree -write-pcs -use-query-log=all:pc,all:smt2 -exit-on-error #-debug-subsumption=3 -debug-state=3

# We silence int to pointer conversion warning
EXTRA_CFLAGS=-Wno-int-conversion

# This is for the options passed onto the tested program, e.g.,
# --sym-arg
PROGRAM_OPTIONS=

TARGETS=$(patsubst %.c,%.tx,$(wildcard *c))

# LLBMC options can be set here; when empty, default options will be
# used instead.
LLBMC_OPTIONS=

include ../Makefile.common

clean: standard-clean

