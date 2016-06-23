# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore

EXTRA_OPTIONS=-interpolation-stat

COREUTILS_DIR=coreutils-6.10
COREUTILS_LLVM_DIR=${COREUTILS_DIR}/obj-llvm
COREUTILS_GCOV_DIR=${COREUTILS_DIR}/obj-gcov


include ../Makefile.common

# The first target (default)
all: cat

build: ${COREUTILS_LLVM_DIR} ${COREUTILS_GCOV_DIR}

${COREUTILS_GCOV_DIR}:
	@echo =================================================================
	@echo Building Coreutils using GCC ...
	@echo =================================================================
	rm -rf ${COREUTILS_GCOV_DIR}	
	mkdir ${COREUTILS_GCOV_DIR}
	( cd ${COREUTILS_GCOV_DIR}; \
		export PATH=${EXTRA_PATH}:$$PATH; \
		../configure --disable-nls CFLAGS="-g -fprofile-arcs -ftest-coverage"; \
		make; \
		make -C src arch hostname \
	)

${COREUTILS_LLVM_DIR}:
	@echo =================================================================
	@echo Building Coreutils using LLVM ...
	@echo =================================================================
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/x86_64-linux-gnu
	rm -rf ${COREUTILS_LLVM_DIR}	
	mkdir ${COREUTILS_LLVM_DIR}
	( cd ${COREUTILS_LLVM_DIR}; \
		export LLVM_COMPILER=clang; \
		export PATH=${EXTRA_PATH}:$$PATH; \
		export CC=${WHOLE_PROGRAM_LLVM}/wllvm; \
		export CXX=${WHOLE_PROGRAM_LLVM}/wllvm++; \
		../configure --disable-nls CFLAGS="-g"; \
		make ; \
		rm -f src/*.gcov \
	)
	@echo =================================================================
	@echo Creating whole-program bitcode file for each utility ...
	@echo =================================================================
	( cd ${COREUTILS_LLVM_DIR}/src; \
		EXEC_LIST=`ls *.o | sed s\/\\\\.o\\$\/\/`; \
		for EXEC_FILE in $$EXEC_LIST ; do \
			if [ -e $$EXEC_FILE ] ; then \
				${WHOLE_PROGRAM_LLVM}/extract-bc $$EXEC_FILE ; \
			fi ; \
		done \
	)

cat: build
	@echo =================================================================
	@echo Running KLEE on $@ ...
	@echo =================================================================
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -f $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=120 --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc --sym-args 0 3 10 -sym-files 2 8 -max-fail 1 \
	)
	@echo =================================================================
	@echo Running KLEE-generated tests to compute coverage ...
	@echo =================================================================
	( cd ${COREUTILS_GCOV_DIR}/src; \
		for KLEE_TEST in ../../../${COREUTILS_LLVM_DIR}/src/$@.klee/*.ktest ; do \
			${KLEE_REPLAY} ./$@ $$KLEE_TEST ; \
		done ; \
		gcov $@ \
	)

clean:
	rm -rf ${COREUTILS_GCOV_DIR} ${COREUTILS_LLVM_DIR} ${COREUTILS_DIR}/doc/coreutils.info

