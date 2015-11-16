# Makefile to build and run the examples using KLEE.
#
# Copyright 2015 National University of Singapore
#
# This Makefile will create klee output directories
# <example-name>.klee which also contains the .dot files,
# and also <example-name>.inputs that shows the input
# values for each test. 
#
# Sample usages:
#
# To run all examples from the default targets:
#
# make
#
# To run a single example, e.g., number.c from the Hansen,
# Schachte, and Sondergaard's article. These are currenly
# separated from the default targets as they test the
# performance limits of KLEE.
#
# make number.klee
#
# To build an LLVM language file of number.c:
#
# make number.s
#
# To clean the directory:
#
# make clean

CC=llvm-gcc
AS=llvm-gcc -S --emit-llvm
CFLAGS=--emit-llvm -g
KLEE_FLAGS=-write-pcs -use-query-log=all:pc,all:smt2 -search=dfs

# Default targets
TARGETS=addition.klee arraysimple2.klee even.klee polynomial.klee simple.klee

# Targets for examples from Hansen, Schachte, and Sondergaard
HANSEN_TARGETS=number.klee wegner.klee multiply.klee

#

INPUT_TARGETS=$(subst .klee,.inputs,${TARGETS})
IR_TARGETS=$(subst .klee,.s,${TARGETS})

all: all-ir ${INPUT_TARGETS}

all-ir: ${IR_TARGETS}

clean:
	rm -f klee-last *.o *.s *~ *.inputs core 
	rm -rf ${TARGETS} ${HANSEN_TARGETS}

# To prevent the removal of *.klee subdirectories
.PRECIOUS: %.klee

.SUFFIXES: .klee .inputs

.o.klee:
	klee ${KLEE_FLAGS} -output-dir=$@ $<
	opt -analyze -dot-cfg $<
	mv *.dot $@

.klee.inputs:
	for KTEST in $</*.ktest ; do \
		( ( ktest-tool --write-ints $$KTEST ) >> $@ ) ; \
	done

.c.s:
	${AS} $<
