# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore
#
# Symbolic arguments for testing coreutils is following
# http://klee.github.io/docs/coreutils-experiments/

EXTRA_OPTIONS=-interpolation-stat

COREUTILS_DIR=${CURDIR}/coreutils-6.10
COREUTILS_LLVM_DIR=${COREUTILS_DIR}/obj-llvm
COREUTILS_GCOV_DIR=${COREUTILS_DIR}/obj-gcov

BASH=/bin/bash

# From http://klee.github.io/docs/coreutils-experiments/
KLEE_COREUTILS_OPTIONS=--simplify-sym-indices --write-cvcs --write-cov --output-module \
	--max-memory=1000 --disable-inlining --optimize --use-forked-solver \
	--use-cex-cache --libc=uclibc --posix-runtime \
	--allow-external-sym-calls --only-output-states-covering-new \
	--max-sym-array-size=4096 --max-instruction-time=30. --max-time=3600. \
	--watchdog --max-memory-inhibit=false --max-static-fork-pct=1 \
	--max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal \
	--randomize-fork --search=random-path --search=nurs:covnew \
	--use-batching-search --batch-instructions=10000

# Comment this out if the above options are preferred
KLEE_COREUTILS_OPTIONS=--libc=uclibc --posix-runtime --optimize --max-time=60.

# From http://klee.github.io/docs/coreutils-experiments/
# Some of these, e.g., [, have no .bc file: Why?
TARGETS=[ arch base64 basename cat chcon chgrp chmod chown chroot cksum comm cp cpslit cut date dd df dircolors dirname du echo env expand expr factor FALSE fmt fold head hostid hostname id ginstall join kill link ln logname ls md5sum mkdir mkfifo mknod mktemp mv nice nl nohup od paste pathchk pinky pr printenv printf ptx pwd readlink rm rmdir runcon seq setuidgid shred shuf sleep sort split stat stty sum sync tac tail tee touch tr tsort tty uname unexpand uniq unlink uptime users wc whoami who yes 

DEFAULT_ARGS=--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout
DD_ARGS=--sym-args 0 3 10 --sym-files 1 8 -sym-stdin 8 --sym-stdout
DIRCOLORS_ARGS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout
ECHO_ARGS=--sym-args 0 4 300 --sym-files 2 30 -sym-stdin 30 --sym-stdout
EXPR_ARGS=--sym-args 0 1 10 --sym-args 0 3 2 --sym-stdout
MKNOD_ARGS=--sym-args 0 1 10 --sym-args 0 3 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout
OD_ARGS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout
PATHCHK_ARGS=--sym-args 0 1 2 --sym-args 0 1 300 --sym-files 1 8 -sym-stdin 8 --sym-stdout
PRINTF_ARGS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout

KLEE_TARGETS=$(TARGETS:=.klee)

KLEESTP_TARGETS=$(TARGETS:=.stpklee)

# The first target (default)
all: ${KLEE_TARGETS} ${KLEESTP_TARGETS}

include ../Makefile.common

build: ${COREUTILS_LLVM_DIR} ${COREUTILS_GCOV_DIR} test.env

test.env:
	env -i ${BASH} -c '( source testing-env.sh ; env > test.env )'

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
	mkdir sandbox
	( cd sandbox ; \
		ln -s /dev/null a ; \
		ln -s /dev/random b ; \
		echo "#!/bin/sh" > c ; \
		echo "echo \"Hello world!\"" >> c ; \
		chmod +x c ; \
		touch d ; \
		mkdir e \
	)

%.klee: build sandbox
	@echo =================================================================
	@echo Running Tracer-X on $* ...
	@echo =================================================================
	if [ $* = "dd" ]; then \
		PROGRAM_ARGS="${DD_ARGS}" ; \
	elif [ $* = "dircolors" ]; then \
		PROGRAM_ARGS="${DIRCOLORS_ARGS}" ; \
	elif [ $* = "echo" ]; then \
		PROGRAM_ARGS="${ECHO_ARGS}" ; \
	elif [ $* = "expr" ]; then \
		PROGRAM_ARGS="${EXPR_ARGS}" ; \
	elif [ $* = "mknod" ]; then \
		PROGRAM_ARGS="${MKNOD_ARGS}" ; \
	elif [ $* = "od" ]; then \
		PROGRAM_ARGS="${OD_ARGS}" ; \
	elif [ $* = "pathchk" ]; then \
		PROGRAM_ARGS="${PATHCHK_ARGS}" ; \
	elif [ $* = "printf" ]; then \
		PROGRAM_ARGS="${PRINTF_ARGS}" ; \
	else \
		PROGRAM_ARGS="${DEFAULT_ARGS}" ; \
	fi ; \
	rm -rf $@; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIB} time ${KLEE} ${KLEE_FLAGS} ${KLEE_COREUTILS_OPTIONS} --environ=${CURDIR}/test.env --run-in=${CURDIR}/sandbox -output-dir=${CURDIR}/$@ ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_ARGS -max-fail 1 ; \
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	( cd ${COREUTILS_GCOV_DIR}/src ; \
		${KLEE_REPLAY} $* ${CURDIR}/$@/*.ktest ; \
		gcov $* ) > ${CURDIR}/$@/CoverageLog.txt 2>&1; \

%.stpklee: build sandbox
	@echo =================================================================
	@echo Running KLEE with STP on $* ...
	@echo =================================================================
	if [ $* = "dd" ]; then \
		PROGRAM_ARGS="${DD_ARGS}" ; \
	elif [ $* = "dircolors" ]; then \
		PROGRAM_ARGS="${DIRCOLORS_ARGS}" ; \
	elif [ $* = "echo" ]; then \
		PROGRAM_ARGS="${ECHO_ARGS}" ; \
	elif [ $* = "expr" ]; then \
		PROGRAM_ARGS="${EXPR_ARGS}" ; \
	elif [ $* = "mknod" ]; then \
		PROGRAM_ARGS="${MKNOD_ARGS}" ; \
	elif [ $* = "od" ]; then \
		PROGRAM_ARGS="${OD_ARGS}" ; \
	elif [ $* = "pathchk" ]; then \
		PROGRAM_ARGS="${PATHCHK_ARGS}" ; \
	elif [ $* = "printf" ]; then \
		PROGRAM_ARGS="${PRINTF_ARGS}" ; \
	else \
		PROGRAM_ARGS="${DEFAULT_ARGS}" ; \
	fi ; \
	rm -rf $@; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIB} time ${KLEE} ${KLEE_FLAGS} ${KLEE_COREUTILS_OPTIONS} --select-solver=stp --environ=${CURDIR}/test.env --run-in=sandbox -output-dir=${CURDIR}/$@ ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_ARGS -max-fail 1 ;
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	( cd ${COREUTILS_GCOV_DIR}/src ; \
		${KLEE_REPLAY} $* ${CURDIR}/$@/*.ktest ; \
		gcov $* ) > ${CURDIR}/$@/CoverageLog.txt 2>&1; \

clean:
	rm -rf ${KLEE_TARGETS} ${KLEESTP_TARGETS} sandbox sandbox.temps test.env

realclean: clean
	rm -rf ${COREUTILS_GCOV_DIR} ${COREUTILS_LLVM_DIR} 

