# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore

EXTRA_OPTIONS=-interpolation-stat

COREUTILS_DIR=coreutils-6.10

include ../Makefile.common

# The first target (default)
all: llvm gcov

gcov: 
	rm -rf ${COREUTILS_DIR}/obj-gcov	
	mkdir ${COREUTILS_DIR}/obj-gcov
	( cd ${COREUTILS_DIR}/obj-gcov; \
		export PATH=${EXTRA_PATH}:$$PATH; \
		../configure --disable-nls CFLAGS="-g -fprofile-arcs -ftest-coverage"; \
		make; \
		make -C src arch hostname \
	)

llvm:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/x86_64-linux-gnu
	rm -rf ${COREUTILS_DIR}/obj-llvm	
	mkdir ${COREUTILS_DIR}/obj-llvm
	( cd ${COREUTILS_DIR}/obj-llvm; \
		export LLVM_COMPILER=clang; \
		export PATH=${EXTRA_PATH}:$$PATH; \
		export CC=${WHOLE_PROGRAM_LLVM}/wllvm; \
		export CXX=/${WHOLE_PROGRAM_LLVM}/wllvm++; \
		../configure --disable-nls CFLAGS="-g"; \
		make \
	)

cat: llvm gcov
	rm -f cat.bc
	rm -rf tracerx-cat
	cd ${COREUTILS_DIR}/obj-llvm/src; ${WHOLE_PROGRAM_LLVM}/extract-bc cat; ${KLEE} ${KLEE_FLAGS} -max-time=120 --libc=uclibc --posix-runtime -optimize ./cat.bc --sym-args 0 3 10 -sym-files 2 8 -max-fail 1;
	cd ${COREUTILS_DIR}/obj-gcov/src; rm -f *.gcda; ${KLEE_REPLAY} ./cat ${COREUTILS_DIR}/obj-llvm/src/klee-last/*.ktest; cd ${COREUTILS_DIR}/obj-gcov/src; gcov cat;\

clean:
	rm -rf ${COREUTILS_DIR}/obj-gcov
	rm -rf ${COREUTILS_DIR}/obj-llvm
