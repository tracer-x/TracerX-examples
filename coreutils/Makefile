# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore
#
# Symbolic arguments for testing coreutils is following http://klee.github.io/docs/coreutils-experiments/

EXTRA_OPTIONS=-interpolation-stat

COREUTILS_DIR=${CURDIR}/coreutils-6.10
COREUTILS_LLVM_DIR=${COREUTILS_DIR}/obj-llvm
COREUTILS_GCOV_DIR=${COREUTILS_DIR}/obj-gcov

SANDBOX=/tmp/sandbox
BASH=/bin/bash

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

build: ${COREUTILS_LLVM_DIR} ${COREUTILS_GCOV_DIR} sandbox

${COREUTILS_GCOV_DIR}:
	@echo =================================================================
	@echo Building Coreutils using GCC ...
	@echo =================================================================
	rm -rf ${COREUTILS_GCOV_DIR}	
	mkdir ${COREUTILS_GCOV_DIR}
	( cd ${COREUTILS_GCOV_DIR}; \
		export PATH=${EXTRA_PATH}:$$PATH; \
		unset C_INCLUDE_PATH; \
		unset CPLUS_INCLUDE_PATH; \
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
		unset C_INCLUDE_PATH; \
		unset CPLUS_INCLUDE_PATH; \
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

sandbox:
	# The testing sandbox reconstructed here is from
	# http://www.doc.ic.ac.uk/~cristic/klee/klee-cu-sandbox.html
	@echo =================================================================
	@echo Creating the sandbox ...
	@echo =================================================================
	rm -rf ${SANDBOX}
	mkdir ${SANDBOX} 
	( cd ${SANDBOX} ; \
		ln -s /dev/null a ; \
		ln -s /dev/random b ; \
		echo "#!/bin/sh" > c ; \
		echo "echo \"Hello world!\"" >> c ; \
		chmod +x c ; \
		touch d ; \
		mkdir e \
	)

${TARGET}: build sandbox
	@echo =================================================================
	@echo Running Tracerx on $@ ...
	@echo =================================================================
	( if [ $@ = "dd" ]; then \
			PROGRAM_ARGS="${DD_ARGS}" ; \
		elif [ $@ = "dircolors" ]; then \
			PROGRAM_ARGS="${DIRCOLORS_ARGS}" ; \
		elif [ $@ = "echo" ]; then \
			PROGRAM_ARGS="${ECHO_ARGS}" ; \
		elif [ $@ = "expr" ]; then \
			PROGRAM_ARGS="${EXPR_ARGS}" ; \
		elif [ $@ = "mknod" ]; then \
			PROGRAM_ARGS="${MKNOD_ARGS}" ; \
		elif [ $@ = "od" ]; then \
			PROGRAM_ARGS="${OD_ARGS}" ; \
		elif [ $@ = "pathchk" ]; then \
			PROGRAM_ARGS="${PATHCHK_ARGS}" ; \
		elif [ $@ = "printf" ]; then \
			PROGRAM_ARGS="${PRINTF_ARGS}" ; \
		else \
			PROGRAM_ARGS="${DEFAULT_ARGS}" ; \
		fi ; \
		( cd ${SANDBOX}; \
			rm -rf $@.klee; \
			env -i ${BASH} -c '(source ${CURDIR}/testing-env.sh ; LD_LIBRARY_PATH=${EXTRA_LD_LIB} time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$@.klee ${COREUTILS_LLVM_DIR}/src/$@.bc $$PROGRAM_ARGS -max-fail 1)' ; \
		); \
	)
	@echo =================================================================
	@echo Running Tracerx-generated tests to compute coverage ...
	@echo =================================================================
	( cd ${SANDBOX}; \
		${KLEE_REPLAY} ${COREUTILS_GCOV_DIR}/src/$@ $$KLEE_TEST ${COREUTILS_LLVM_DIR}/src/$@.klee/*.ktest ; \
		gcov ${COREUTILS_GCOV_DIR}/src/$@ \
	)

%.stp: build
	@echo =================================================================
	@echo Running KLEE on $* ...
	@echo =================================================================
	#$(eval KLEE = /home/felicia/git/original/klee/Release+Asserts/bin/klee)
	#$(eval KLEE_STATS= /home/felicia/git/original/klee/Release+Asserts/bin/klee-stats)	
	#$(eval KLEE_REPLAY= /home/felicia/git/original/klee/Release+Asserts/bin/klee-replay)
	#$(eval KTEST_TOOL= /home/felicia/git/original/klee/Release+Asserts/bin/ktest-tool)
	$(eval EXTRA_OPTIONS = )
	@if [ $* != "dd" ] && [ $* != "dircolors" ] && [ $* != "echo" ] && [ $* != "expr" ] && [ $* != "mknod" ] && [ $* != "od" ] && [ $* != "pathchk" ] && [ $* != "printf" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${DEFAULT_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $* = "dd" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${DD_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $* = "dircolors" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${DIRCOLORS_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $* = "echo" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${ECHO_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $* = "expr" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${EXPR_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $* = "mknod" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${MKNOD_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $* = "od" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${OD_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $* = "pathchk" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${PATHCHK_ARGS} -max-fail 1; \
	); \
	fi
	@if [ $* = "printf" ]; then\
	( cd ${COREUTILS_LLVM_DIR}/src; \
		rm -rf $*.stpklee; \
		time ${KLEE} ${KLEE_FLAGS} -max-time=${MAX_TIME} --libc=uclibc --posix-runtime -optimize -output-dir=$*.stpklee ./$*.bc ${PRINTF_ARGS} -max-fail 1; \
	); \
	fi	
	@echo =================================================================
	@echo Running KLEE-generated tests to compute coverage ...
	@echo =================================================================
	( cd ${COREUTILS_GCOV_DIR}/src; \
		for KLEE_TEST in ../../../${COREUTILS_LLVM_DIR}/src/$*.stpklee/*.ktest ; do \
			${KLEE_REPLAY} ./$* $$KLEE_TEST ; \
		done ; \
		gcov $* \
	)

clean:
	rm -rf ${COREUTILS_GCOV_DIR} ${COREUTILS_LLVM_DIR} ${SANDBOX}

