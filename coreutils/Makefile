# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore
#
# Symbolic arguments for testing coreutils is following http://klee.github.io/docs/coreutils-experiments/

EXTRA_OPTIONS=-interpolation-stat

COREUTILS_DIR=coreutils-6.10
COREUTILS_LLVM_DIR=${COREUTILS_DIR}/obj-llvm
COREUTILS_GCOV_DIR=${COREUTILS_DIR}/obj-gcov

TARGET=[ arch base64 basename cat chcon chgrp chmod chown chroot cksum comm cp cpslit cut date dd df dircolors dirname du echo env expand expr factor FALSE fmt fold head hostid hostname id ginstall join kill link ln logname ls md5sum mkdir mkfifo mknod mktemp mv nice nl nohup od paste pathchk pinky pr printenv printf ptx pwd readlink rm rmdir runcon seq setuidgid shred shuf sleep sort split stat stty sum sync tac tail tee touch tr tsort tty uname unexpand uniq unlink uptime users wc whoami who yes 
MAX_TIME=60
DEFAULT_ARGS=--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout
DD_ARGS=--sym-args 0 3 10 --sym-files 1 8 -sym-stdin 8 --sym-stdout
DIRCOLORS_ARGS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout
ECHO_ARGS=--sym-args 0 4 300 --sym-files 2 30 -sym-stdin 30 --sym-stdout
EXPR_ARGS=--sym-args 0 1 10 --sym-args 0 3 2 --sym-stdout
MKNOD_ARGS=--sym-args 0 1 10 --sym-args 0 3 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout
OD_ARGS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout
PATHCHK_ARGS=--sym-args 0 1 2 --sym-args 0 1 300 --sym-files 1 8 -sym-stdin 8 --sym-stdout
PRINTF_ARGS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout

include ../Makefile.common

# The first target (default)
all: ${TARGET}

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

${TARGET}: build
	@echo =================================================================
	@echo Running KLEE on $@ ...
	@echo =================================================================
	@if [ $@ != "dd" ] && [ $@ != "dircolors" ] && [ $@ != "echo" ] && [ $@ != "expr" ] && [ $@ != "mknod" ] && [ $@ != "od" ] && [ $@ != "pathchk" ] && [ $@ != "printf" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${DEFAULT_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $@ = "dd" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${DD_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $@ = "dircolors" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${DIRCOLORS_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $@ = "echo" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${ECHO_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $@ = "expr" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${EXPR_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $@ = "mknod" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${MKNOD_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $@ = "od" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${OD_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $@ = "pathchk" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${PATHCHK_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $@ = "printf" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $@.klee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ./$@.bc ${PRINTF_ARGS} -max-fail 1; \
	); \
	fi	
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

