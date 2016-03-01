# Makefile to build and run the examples using KLEE.
#
# Copyright 2015 National University of Singapore

TARGETS=Regexp.klee \
	bubble.klee

LLBMC=${HOME}/software/llbmc-2013.1-Linux_64

include ../Makefile.common

bubble_llbmc: bubble_llbmc.c
	${CC} -c -g -emit-llvm -I${LLBMC}/examples bubble_llbmc.c -o bubble_llbmc.o
	llbmc -max-loop-iterations=10 bubble_llbmc.o

