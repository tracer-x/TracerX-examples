# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore

EXTRA_OPTIONS=-interpolation-stat

# We remove bubble_llbmc.klee from KLEE targets, as it
# is to be run with LLBMC
TARGETS=$(subst bubble_llbmc.klee,,$(patsubst %.c,%.klee,$(wildcard *.c)))

LLBMC=${HOME}/software/llbmc-2013.1-Linux_64

TR_TARGETS=tr.tr0 tr_nosyscall.tr0 tr_small.tr0

EXTRA_REMOVAL=${TR_TARGETS}

include ../Makefile.common

###############################################################################
# Below are special targets for special run configurations                    #
###############################################################################

bubble_llbmc: bubble_llbmc.c
	${CC} -c -g -emit-llvm -I${LLBMC}/examples bubble_llbmc.c -o bubble_llbmc.o
	llbmc -max-loop-iterations=10 bubble_llbmc.o

echo_small: echo_small.bc
	time ${KLEE} -max-time=600 -interpolation-stat --only-output-states-covering-new --libc=uclibc --posix-runtime --allow-external-sym-calls echo_small.bc --sym-args 0 2 4

# For running Minix tr versions
tr: ${TR_TARGETS}
	rm -rf klee-*
	rm -f $^

.SUFFIXES: .tr0

.bc.tr0:
	rm -rf $@ klee-*
	time ${KLEE} --max-time=120 -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls -output-tree $< --sym-arg 1 --sym-arg 1 --sym-files 2 2000 --max-fail 1
	rm -rf klee-*
	time ${KLEE} --max-time=120 -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls $< --sym-arg 2 --sym-arg 2 --sym-files 2 2000 --max-fail 1
	rm -rf klee-*
	time ${KLEE} --max-time=120 -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls $< --sym-arg 3 --sym-arg 3 --sym-files 2 2000 --max-fail 1
	touch $@
