# Copyright 2015 National University of Singapore

CC=llvm-gcc
CFLAGS=--emit-llvm -g
TARGETS=branch.klee array1.klee array2.klee no_grounding.klee

all: ${TARGETS}

clean:
	rm -f klee-last *.o *~ core
	rm -rf ${TARGETS}

.SUFFIXES: .klee

.o.klee:
	klee -output-dir=$@ $<
