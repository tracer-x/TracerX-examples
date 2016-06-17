# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore

##  Please follow all the steps one by one:
##    
##  1. 'make llvm' : Build Coreutils with LLVM
##  2. 'make gcov' : Build Coreutils with GCOV
##  notes: step 1 and 2 only need to be executed once
##  3. 'make <program_name>'
##	<program_name> is one of the program in the coreutils-6.10/obj-llvm/src
##	The output will be the result of Tracer-x run on the input and it's coverage.

#KLEE=klee
#KLEE_STATS=klee-stats
#KLEE_REPLAY=klee-replay
#KTEST_TOOL=ktest-tool
EXTRA_OPTIONS=-interpolation-stat

COREUTILS=coreutils-6.10
WHOLE_PROGRAM_LLVM=/home/felicia/whole-program-llvm

KLEE=/home/felicia/git/tracerx/klee/Release+Asserts/bin/klee
KLEE_REPLAY=/home/felicia/git/tracerx/klee/Release+Asserts/bin/klee-replay
KTEST_TOOL=/home/felicia/git/tracerx/klee/Release+Asserts/bin/ktest-tool
KLEE_EXAMPLES=/home/felicia/git/klee-examples/coreutils

KLEE_FLAGS=${EXTRA_OPTIONS} -search=dfs

gcov: 
	rm -rf ${COREUTILS}/obj-gcov	
	mkdir ${COREUTILS}/obj-gcov
	cd ${COREUTILS}/obj-gcov; ../configure --disable-nls CFLAGS="-g -fprofile-arcs -ftest-coverage"; make; make -C src arch hostname;

	
llvm:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/x86_64-linux-gnu
	rm -rf ${COREUTILS}/obj-llvm	
	mkdir ${COREUTILS}/obj-llvm
	cd ${COREUTILS}/obj-llvm; ../configure --disable-nls CFLAGS="-g"; export CC=${WHOLE_PROGRAM_LLVM}/wllvm; export CXX=/${WHOLE_PROGRAM_LLVM}/wllvm++; ../configure --disable-nls CFLAGS="-g"; make;\
	
cat:
	rm -f cat.bc
	rm -rf tracerx-cat
	cd ${COREUTILS}/obj-llvm/src; ${WHOLE_PROGRAM_LLVM}/extract-bc cat; ${KLEE} ${KLEE_FLAGS} -max-time=120 --libc=uclibc --posix-runtime -optimize ./cat.bc --sym-args 0 3 10 -sym-files 2 8 -max-fail 1;
	cd ${KLEE_EXAMPLES}/${COREUTILS}/obj-gcov/src; rm -f *.gcda; ${KLEE_REPLAY} ./cat ${KLEE_EXAMPLES}/${COREUTILS}/obj-llvm/src/klee-last/*.ktest; cd ${KLEE_EXAMPLES}/${COREUTILS}/obj-gcov/src; gcov cat;\

clean:
	rm -rf ${COREUTILS}/obj-gcov
	rm -rf ${COREUTILS}/obj-llvm
