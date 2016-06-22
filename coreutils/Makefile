# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore

EXTRA_OPTIONS=-interpolation-stat

COREUTILS_DIR=coreutils-6.10
COREUTILS_LLVM_DIR=${COREUTILS_DIR}/obj-llvm
COREUTILS_GCOV_DIR=${COREUTILS_DIR}/obj-gcov

include ../Makefile.common

# The first target (default)
all: ${COREUTILS_LLVM_DIR} ${COREUTILS_GCOV_DIR}

${COREUTILS_GCOV_DIR}: 
	rm -rf ${COREUTILS_GCOV_DIR}	
	mkdir ${COREUTILS_GCOV_DIR}
	( cd ${COREUTILS_GCOV_DIR}; \
		export PATH=${EXTRA_PATH}:$$PATH; \
		../configure --disable-nls CFLAGS="-g -fprofile-arcs -ftest-coverage"; \
		make; \
		make -C src arch hostname \
	)

${COREUTILS_LLVM_DIR}:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/x86_64-linux-gnu
	rm -rf ${COREUTILS_LLVM_DIR}	
	mkdir ${COREUTILS_LLVM_DIR}
	( cd ${COREUTILS_LLVM_DIR}; \
		export LLVM_COMPILER=clang; \
		export PATH=${EXTRA_PATH}:$$PATH; \
		export CC=${WHOLE_PROGRAM_LLVM}/wllvm; \
		export CXX=${WHOLE_PROGRAM_LLVM}/wllvm++; \
		../configure --disable-nls CFLAGS="-g"; \
		make \
	)

cat: all
	rm -f cat.bc
	rm -rf tracerx-cat
	cd ${COREUTILS_LLVM_DIR}/src; ${WHOLE_PROGRAM_LLVM}/extract-bc cat; ${KLEE} ${KLEE_FLAGS} -max-time=120 --libc=uclibc --posix-runtime -optimize ./cat.bc --sym-args 0 3 10 -sym-files 2 8 -max-fail 1
	cd ${COREUTILS_GCOV_DIR}/src; rm -f *.gcda; ${KLEE_REPLAY} ./cat ${COREUTILS_LLVM_DIR}/src/klee-last/*.ktest; cd ${COREUTILS_GCOV_DIR}/src; gcov cat

clean:
	rm -rf ${COREUTILS_GCOV_DIR} ${COREUTILS_LLVM_DIR} doc

