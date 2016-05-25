# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore

EXTRA_OPTIONS=-interpolation-stat

# We remove bubble_llbmc.klee from KLEE targets, as it
# is to be run with LLBMC
TARGETS=$(subst bubble_llbmc.klee,,$(patsubst %.c,%.klee,$(wildcard *.c)))

LLBMC=${HOME}/software/llbmc-2013.1-Linux_64

ECHO_TARGETS=echo_nosyscall.echo0 echo_small.echo0
TR_TARGETS=tr.tr0 tr_nosyscall.tr0 tr_small.tr0
BUBBLE_TARGETS=bubble9.bubble0 bubble12.bubble0 bubble9_unsafe.bubble0 bubble12_unsafe.bubble0

EXTRA_REMOVAL=${TR_TARGETS}

include ../Makefile.common

#################################################################################
# Below are special targets for special run configurations                      #
#                                                                               #
# To run all programs under specific group targets, please run:                 #
#   Make <group_target>                                                         #
#     Example:                                                                  #
#       Make echo  ==> run echo_nosyscall and echo_small                        #
#       Make tr  ==> run tr, tr_nosyscall, and tr_small                         #
#       Make bubble  ==> run bubble9, bubble12, bubble9_unsafe, bubble12_unsafe #
# To run only a specific program, please run:                                   #
#   Make <program_name>.<suffixes_group>                                        #
#     Example:                                                                  #
#       Make echo_nosyscall.echo0 (only run echo_nosyscall)                     #
#       Make tr_nosyscall.tr0 (only run tr_nosyscall)                           #
#       Make bubble9.bubble0 (only run bubble9)                                 #
#################################################################################

bubble_llbmc: bubble_llbmc.c
	${CC} -c -g -emit-llvm -I${LLBMC}/examples bubble_llbmc.c -o bubble_llbmc.o
	llbmc -max-loop-iterations=10 bubble_llbmc.o

echo: ${ECHO_TARGETS}
	rm -rf klee-*
	rm -f $^

# For running Minix tr versions
tr: ${TR_TARGETS}
	rm -rf klee-*
	rm -f $^

bubble: ${BUBBLE_TARGETS}
	rm -rf klee-*
	rm -f $^

.SUFFIXES: .tr0 .echo0 .bubble0

.bc.echo0:
	rm -rf $@ klee-*
	time ${KLEE} -max-time=600 -interpolation-stat --only-output-states-covering-new --libc=uclibc --posix-runtime --allow-external-sym-calls $< --sym-args 0 2 4
	touch $@

.bc.tr0:
	rm -rf $@ klee-*
	time ${KLEE} --max-time=120 -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls -output-tree $< --sym-arg 1 --sym-arg 1 --sym-files 2 2000 --max-fail 1
	rm -rf klee-*
	time ${KLEE} --max-time=120 -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls $< --sym-arg 2 --sym-arg 2 --sym-files 2 2000 --max-fail 1
	rm -rf klee-*
	time ${KLEE} --max-time=120 -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls $< --sym-arg 3 --sym-arg 3 --sym-files 2 2000 --max-fail 1
	touch $@

.bc.bubble0:
	rm -rf $@ klee-*
	time ${KLEE} -max-time=120 -interpolation-stat --only-output-states-covering-new $<
	touch $@
	
