# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore
#
# Symbolic arguments for testing coreutils is following
# http://klee.github.io/docs/coreutils-experiments/

COREUTILS_DIR=${CURDIR}/coreutils-6.10
COREUTILS_LLVM_DIR=${COREUTILS_DIR}/obj-llvm
COREUTILS_COV_DIR=${COREUTILS_DIR}/obj-cov
COREUTILS_SRC=${COREUTILS_DIR}/src
CFLAGS_LLBMC_COREUTILS=-g -I${COREUTILS_LLVM_DIR}/lib -I${COREUTILS_SRC} -I/${COREUTILS_DIR}/lib
LLBMC_OUTPUT_DIR=${CURDIR}/LLBMC_OUTPUT
LLBMC_OPTIONS=--ignore-missing-function-bodies -function-name=main -max-loop-iterations=5 -max-function-call-depth=10

BASH=/bin/bash

# From http://klee.github.io/docs/coreutils-experiments/
TARGETS=[.tx arch.tx base64.tx basename.tx cat.tx chcon.tx chgrp.tx chmod.tx chown.tx chroot.tx cksum.tx comm.tx cp.tx csplit.tx cut.tx date.tx dd.tx df.tx dircolors.tx dirname.tx du.tx echo.tx env.tx expand.tx expr.tx factor.tx false.tx fmt.tx fold.tx head.tx hostid.tx hostname.tx id.tx ginstall.tx join.tx kill.tx link.tx ln.tx logname.tx ls.tx md5sum.tx mkdir.tx mkfifo.tx mknod.tx mktemp.tx mv.tx nice.tx nl.tx nohup.tx od.tx paste.tx pathchk.tx pinky.tx pr.tx printenv.tx printf.tx ptx.tx pwd.tx readlink.tx rm.tx rmdir.tx runcon.tx seq.tx setuidgid.tx shred.tx shuf.tx sleep.tx sort.tx split.tx stat.tx stty.tx sum.tx sync.tx tac.tx tail.tx tee.tx touch.tx tr.tx tsort.tx tty.tx uname.tx unexpand.tx uniq.tx unlink.tx uptime.tx users.tx wc.tx whoami.tx who.tx yes.tx 

DEFAULT_OPTIONS=--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout
DD_OPTIONS=--sym-args 0 3 10 --sym-files 1 8 -sym-stdin 8 --sym-stdout
DIRCOLORS_OPTIONS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout
ECHO_OPTIONS=--sym-args 0 4 300 --sym-files 2 30 -sym-stdin 30 --sym-stdout
EXPR_OPTIONS=--sym-args 0 1 10 --sym-args 0 3 2 --sym-stdout
MKNOD_OPTIONS=--sym-args 0 1 10 --sym-args 0 3 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout
OD_OPTIONS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout
PATHCHK_OPTIONS=--sym-args 0 1 2 --sym-args 0 1 300 --sym-files 1 8 -sym-stdin 8 --sym-stdout
PRINTF_OPTIONS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout

# Coreutils benchmark set for November/December 2016 experiment
EXPERIMENT_SET=comm cut dirname expand factor join split sum uniq

EXPERIMENT_CSV=experiment.csv

EXPERIMENT_TIMEOUT=3600.

EXPERIMENT_MEMORY=13000

# From http://klee.github.io/docs/coreutils-experiments/
# with --search, --max-time, and --max-memory excluded to be
# specified via KLEE_COREUTILS_MORE_OPTIONS or
# KLEE_COREUTILS_DEFAULT_OPTIONS (see below).
KLEE_COREUTILS_BASIC_OPTIONS=--simplify-sym-indices --write-cvcs --write-cov --output-module \
	--disable-inlining --optimize --use-forked-solver \
	--use-cex-cache --libc=uclibc --posix-runtime \
	--allow-external-sym-calls --only-output-states-covering-new \
	--max-sym-array-size=4096 --max-instruction-time=30. \
	--watchdog --max-memory-inhibit=false --max-static-fork-pct=1 \
	--max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal \
	--randomize-fork \
	--use-batching-search --batch-instructions=10000

# The defaults from http://klee.github.io/docs/coreutils-experiments/
KLEE_COREUTILS_DEFAULT_OPTIONS=--search=random-path --max-memory=1000 --search=nurs:covnew -max-time=3600.

LLBMC_EXPERIMENT_CSV=llbmc-${EXPERIMENT_CSV}

KLEE_TARGETS1=$(EXPERIMENT_SET:=.klee1)
KLEE_TARGETS2=$(EXPERIMENT_SET:=.klee2)
TRACERX_TARGETS1=$(EXPERIMENT_SET:=.tx1)
TRACERX_TARGETS2=$(EXPERIMENT_SET:=.tx2)
TRACERX_TARGETS3=$(EXPERIMENT_SET:=.tx3)
TRACERX_TARGETS4=$(EXPERIMENT_SET:=.tx4)
TRACERX_TARGETS5=$(EXPERIMENT_SET:=.tx5)
TRACERX_TARGETS6=$(EXPERIMENT_SET:=.tx6)

# The first target (default)
all: ${TARGETS} ${KLEE_TARGETS} ${STPKLEE_TARGETS}

include ../Makefile.common

build: ${COREUTILS_LLVM_DIR} ${COREUTILS_COV_DIR} test.env

test.env:
	env -i ${BASH} -c '( source testing-env.sh ; env > test.env )'

# In the following target:
# * We build src, arch and hostname after make is executed, as it
#   appears that make does not build them.
# * We skip whole-program bitcode creation for groups as it is a script.
${COREUTILS_LLVM_DIR}:
	@echo =================================================================
	@echo Building Coreutils using WLLVM ...
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
		../configure --disable-nls CFLAGS="-g" --enable-install-program=arch,hostname ; \
		make ; \
		make -C src arch hostname \
	)
	@echo =================================================================
	@echo Creating whole-program bitcode file for each utility ...
	@echo =================================================================
	( cd ${COREUTILS_LLVM_DIR}/src; \
		EXEC_LIST=`find . -executable -type f | sed 's/.\/groups//'` ; \
		for EXEC_FILE in $$EXEC_LIST ; do \
			${WHOLE_PROGRAM_LLVM}/extract-bc $$EXEC_FILE ; \
		done \
	)

${COREUTILS_COV_DIR}:
	@echo =================================================================
	@echo Building Coreutils with coverage profiling ...
	@echo =================================================================
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/x86_64-linux-gnu
	rm -rf ${COREUTILS_COV_DIR}	
	mkdir ${COREUTILS_COV_DIR}
	( cd ${COREUTILS_COV_DIR}; \
		export PATH=${EXTRA_PATH}:$$PATH; \
		export CC=clang; \
		export CXX=clang++; \
		unset C_INCLUDE_PATH; \
		unset CPLUS_INCLUDE_PATH; \
		../configure --disable-nls CFLAGS="-g -fprofile-arcs -ftest-coverage" --enable-install-program=arch,hostname ; \
		make ; \
		make -C src arch hostname \
	)

%.klee1 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.klee2 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tx1 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx2 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-subsumption-failure=3 -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx3 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx4 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -max-subsumption-failure=3 -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx5 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -exact-address-interpolant -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx6 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-subsumption-failure=3 -exact-address-interpolant -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

# pr
%.klee7 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-a -sym-stdin 4 --sym-stdout" make $*.klee

%.klee8 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-a -sym-stdin 5 --sym-stdout" make $*.klee

%.klee9 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-a -sym-stdin 6 --sym-stdout" make $*.klee

%.tx7 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-a -sym-stdin 4 --sym-stdout" make $*.tx

%.tx8 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-a -sym-stdin 5 --sym-stdout" make $*.tx

%.tx9 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-a -sym-stdin 6 --sym-stdout" make $*.tx

# cut
%.klee10 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 4 --sym-stdout" make $*.klee

%.klee11 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 5 --sym-stdout" make $*.klee

%.klee12 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 6 --sym-stdout" make $*.klee

%.klee13 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 7 --sym-stdout" make $*.klee

%.tx10 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 4 --sym-stdout" make $*.tx

%.tx11 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 5 --sym-stdout" make $*.tx

%.tx12 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 6 --sym-stdout" make $*.tx

%.tx13 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 7 --sym-stdout" make $*.tx

# printf
%.klee14 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 1 -sym-arg 1 --sym-stdout" make $*.klee

%.klee15 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 2 -sym-arg 1 --sym-stdout" make $*.klee

%.klee16 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 3 -sym-arg 1 --sym-stdout" make $*.klee

%.tx14 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 1 -sym-arg 1 --sym-stdout" make $*.tx

%.tx15 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 2 -sym-arg 1 --sym-stdout" make $*.tx

%.tx16 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 3 -sym-arg 1 --sym-stdout" make $*.tx

# basename
%.klee17 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout" make $*.klee

%.klee18 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 3 --sym-files 1 8 -sym-stdin 8 --sym-stdout" make $*.klee

%.klee19 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 4 --sym-files 1 8 -sym-stdin 8 --sym-stdout" make $*.klee

%.klee20 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 5 --sym-files 1 8 -sym-stdin 8 --sym-stdout" make $*.klee

%.tx17 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout" make $*.tx

%.tx18 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 3 --sym-files 1 8 -sym-stdin 8 --sym-stdout" make $*.tx

%.tx19 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 4 --sym-files 1 8 -sym-stdin 8 --sym-stdout" make $*.tx

%.tx20 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 5 --sym-files 1 8 -sym-stdin 8 --sym-stdout" make $*.tx

# head
%.klee21 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 2 -sym-stdin 8 --sym-stdout" make $*.klee

%.klee22 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 3 -sym-stdin 8 --sym-stdout" make $*.klee

%.klee23 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 4 -sym-stdin 8 --sym-stdout" make $*.klee

%.tx21 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 2 -sym-stdin 8 --sym-stdout" make $*.tx

%.tx22 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 3 -sym-stdin 8 --sym-stdout" make $*.tx

%.tx23 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 4 -sym-stdin 8 --sym-stdout" make $*.tx

# pathchk
%.klee24 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 13 --sym-stdout" make $*.klee

%.klee25 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 14 --sym-stdout" make $*.klee

%.klee26 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 15 --sym-stdout" make $*.klee

%.klee27 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 16 --sym-stdout" make $*.klee

%.klee28 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 17 --sym-stdout" make $*.klee

%.klee29 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 18 --sym-stdout" make $*.klee

%.tx24 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 13 --sym-stdout" make $*.tx

%.tx25 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 14 --sym-stdout" make $*.tx

%.tx26 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 15 --sym-stdout" make $*.tx

%.tx27 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 16 --sym-stdout" make $*.tx

%.tx28 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 17 --sym-stdout" make $*.tx

%.tx29 :
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-time=${EXPERIMENT_TIMEOUT} -max-memory=${EXPERIMENT_MEMORY} -write-paths" OUTPUT_DIR=${CURDIR}/$@ PROGRAM_OPTIONS="-sym-arg 18 --sym-stdout" make $*.tx

# The following targets can be used for running experiments. The
# conducted experiments involved different option settings of KLEE and
# Tracer-X which can be seen in %.klee... and %.tx... targets.
%.tx: build
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
	@echo =================================================================
	@echo Running Tracer-X on $* ...
	@echo =================================================================
	if [ -z "$$PROGRAM_OPTIONS" ] ; then \
		if [ $* = "dd" ]; then \
			PROGRAM_OPTIONS="${DD_OPTIONS}" ; \
		elif [ $* = "dircolors" ]; then \
			PROGRAM_OPTIONS="${DIRCOLORS_OPTIONS}" ; \
		elif [ $* = "echo" ]; then \
			PROGRAM_OPTIONS="${ECHO_OPTIONS}" ; \
		elif [ $* = "expr" ]; then \
			PROGRAM_OPTIONS="${EXPR_OPTIONS}" ; \
		elif [ $* = "mknod" ]; then \
			PROGRAM_OPTIONS="${MKNOD_OPTIONS}" ; \
		elif [ $* = "od" ]; then \
			PROGRAM_OPTIONS="${OD_OPTIONS}" ; \
		elif [ $* = "pathchk" ]; then \
			PROGRAM_OPTIONS="${PATHCHK_OPTIONS}" ; \
		elif [ $* = "printf" ]; then \
			PROGRAM_OPTIONS="${PRINTF_OPTIONS}" ; \
		else \
			PROGRAM_OPTIONS="${DEFAULT_OPTIONS}" ; \
		fi ; \
	fi ; \
	if [ -z "${OUTPUT_DIR}" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	else \
		OUTPUT_DIR="${OUTPUT_DIR}" ; \
	fi ; \
	rm -rf $$OUTPUT_DIR; \
	KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_MORE_OPTIONS}"; \
	if [ -z "${KLEE_COREUTILS_MORE_OPTIONS}" ] ; then \
		KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	PROGRAM_OPTIONS="$$PROGRAM_OPTIONS -max-fail 1" ; \
	echo PROGRAM_OPTIONS="$$PROGRAM_OPTIONS" ; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} -interpolation-stat ${KLEE_COREUTILS_BASIC_OPTIONS} $$KLEE_COREUTILS_EXTRA_OPTIONS -solver-backend=z3 --environ=${CURDIR}/test.env --run-in=${CURDIR}/sandbox -output-dir=$$OUTPUT_DIR ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_OPTIONS ; \
	echo -n "$$PROGRAM_OPTIONS" > $$OUTPUT_DIR/ProgramOptions.txt ; \
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Create SVGs from tree.dot file if any ...
	@echo =================================================================
	if [ -z "${OUTPUT_DIR}" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	else \
		OUTPUT_DIR="${OUTPUT_DIR}" ; \
	fi ; \
	if [ -e $$OUTPUT_DIR/tree.dot ]; then \
		dot -Tsvg $$OUTPUT_DIR/tree.dot -o $$OUTPUT_DIR/$*.svg ; \
	fi
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	if [ -z "${OUTPUT_DIR}" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	else \
		OUTPUT_DIR="${OUTPUT_DIR}" ; \
	fi ; \
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"` ; \
	( cd ${COREUTILS_COV_DIR}/src ; \
	        for KTEST in $$OUTPUT_DIR/*.ktest ; do \
			( LD_LIBRARY_PATH=${KLEE_HOME}/lib KTEST_FILE=$$KTEST ${KLEE_REPLAY} $* $$KTEST ) ; \
		done ) ; \
	( cd ${COREUTILS_COV_DIR} ; \
		LINE_COVERAGE_TOTAL=0 ; \
		LCOV_OBJECTS=`find . -name "*.gcda"` ; \
		LCOV_SOURCES="" ; \
		for LCOV_OBJ in $$LCOV_OBJECTS ; do \
			LCOV_NAME=$${LCOV_OBJ%.*} ; \
			LCOV_BASENAME=$$(basename "$${LCOV_NAME}") ; \
			LCOV_DIRNAME=$$(dirname "$${LCOV_OBJ}") ; \
			cd ${COREUTILS_COV_DIR}/$$LCOV_DIRNAME ; \
			NEW_SRC_LIST=`llvm-cov -gcno=./$$LCOV_BASENAME.gcno -gcda=./$$LCOV_BASENAME.gcda | grep '0:Source:' | sed s/-://g | sed s/0:Source://g` ; \
			for NEW_SRC_FILE in $$NEW_SRC_LIST ; do \
				LCOV_SOURCES="$$LCOV_SOURCES ${COREUTILS_COV_DIR}/$$LCOV_DIRNAME/$$NEW_SRC_FILE" ; \
			done ; \
			LINE_COVERAGE=`llvm-cov -gcno=./$$LCOV_BASENAME.gcno -gcda=./$$LCOV_BASENAME.gcda | grep '^[[:space:]]*[[:digit:]]\+' | wc -l`  ; \
			LINE_COVERAGE_TOTAL=`expr $$LINE_COVERAGE_TOTAL + $$LINE_COVERAGE` ; \
		done ; \
		LOC_TOTAL=0 ; \
		for LCOV_SRC in $$LCOV_SOURCES ; do \
			if [ -e $$LCOV_SRC ] ; then \
				LOC=`sloccount $$LCOV_SRC |grep "Total Physical" | sed s/^[[:alpha:],[:space:],\(,\),\=]*//` ; \
				if [ x$$LOC != x ] ; then \
					LOC_TOTAL=`expr $$LOC_TOTAL + $$LOC` ; \
				fi ; \
			fi ; \
		done ; \
		( echo -n $$LINE_COVERAGE_TOTAL > $$OUTPUT_DIR/LcovLog.txt ) ; \
		( echo -n $$LOC_TOTAL > $$OUTPUT_DIR/SLocCountLog.txt ) \
	)
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"`

%.klee: build
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
	@echo =================================================================
	@echo Running KLEE with Z3 on $* ...
	@echo =================================================================
	if [ -z "$$PROGRAM_OPTIONS" ] ; then \
		if [ $* = "dd" ]; then \
			PROGRAM_OPTIONS="${DD_OPTIONS}" ; \
		elif [ $* = "dircolors" ]; then \
			PROGRAM_OPTIONS="${DIRCOLORS_OPTIONS}" ; \
		elif [ $* = "echo" ]; then \
			PROGRAM_OPTIONS="${ECHO_OPTIONS}" ; \
		elif [ $* = "expr" ]; then \
			PROGRAM_OPTIONS="${EXPR_OPTIONS}" ; \
		elif [ $* = "mknod" ]; then \
			PROGRAM_OPTIONS="${MKNOD_OPTIONS}" ; \
		elif [ $* = "od" ]; then \
			PROGRAM_OPTIONS="${OD_OPTIONS}" ; \
		elif [ $* = "pathchk" ]; then \
			PROGRAM_OPTIONS="${PATHCHK_OPTIONS}" ; \
		elif [ $* = "printf" ]; then \
			PROGRAM_OPTIONS="${PRINTF_OPTIONS}" ; \
		else \
			PROGRAM_OPTIONS="${DEFAULT_OPTIONS}" ; \
		fi ; \
	fi ; \
	if [ -z "${OUTPUT_DIR}" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	else \
		OUTPUT_DIR="${OUTPUT_DIR}" ; \
	fi ; \
	rm -rf $$OUTPUT_DIR; \
	KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_MORE_OPTIONS}"; \
	if [ -z "${KLEE_COREUTILS_MORE_OPTIONS}" ] ; then \
		KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	PROGRAM_OPTIONS="$$PROGRAM_OPTIONS -max-fail 1" ; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} -interpolation-stat ${KLEE_COREUTILS_BASIC_OPTIONS} $$KLEE_COREUTILS_EXTRA_OPTIONS -no-interpolation -solver-backend=z3 --environ=${CURDIR}/test.env --run-in=${CURDIR}/sandbox -output-dir=$$OUTPUT_DIR ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_OPTIONS ; \
	echo -n "$$PROGRAM_OPTIONS" > $$OUTPUT_DIR/ProgramOptions.txt ; \
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Create SVGs from tree.dot file if any ...
	@echo =================================================================
	if [ -z "${OUTPUT_DIR}" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	else \
		OUTPUT_DIR="${OUTPUT_DIR}" ; \
	fi ; \
	if [ -e $$OUTPUT_DIR/tree.dot ]; then \
		dot -Tsvg $$OUTPUT_DIR/tree.dot -o $$OUTPUT_DIR/$*.svg ; \
	fi
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	if [ -z "${OUTPUT_DIR}" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	else \
		OUTPUT_DIR="${OUTPUT_DIR}" ; \
	fi ; \
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"` ; \
	( cd ${COREUTILS_COV_DIR}/src ; \
	        for KTEST in $$OUTPUT_DIR/*.ktest ; do \
			( LD_LIBRARY_PATH=${KLEE_HOME}/lib KTEST_FILE=$$KTEST ${KLEE_REPLAY} $* $$KTEST ) ; \
		done ) ; \
	( cd ${COREUTILS_COV_DIR} ; \
		LINE_COVERAGE_TOTAL=0 ; \
		LCOV_OBJECTS=`find . -name "*.gcda"` ; \
		LCOV_SOURCES="" ; \
		for LCOV_OBJ in $$LCOV_OBJECTS ; do \
			LCOV_NAME=$${LCOV_OBJ%.*} ; \
			LCOV_BASENAME=$$(basename "$${LCOV_NAME}") ; \
			LCOV_DIRNAME=$$(dirname "$${LCOV_OBJ}") ; \
			cd ${COREUTILS_COV_DIR}/$$LCOV_DIRNAME ; \
			NEW_SRC_LIST=`llvm-cov -gcno=./$$LCOV_BASENAME.gcno -gcda=./$$LCOV_BASENAME.gcda | grep '0:Source:' | sed s/-://g | sed s/0:Source://g` ; \
			for NEW_SRC_FILE in $$NEW_SRC_LIST ; do \
				LCOV_SOURCES="$$LCOV_SOURCES ${COREUTILS_COV_DIR}/$$LCOV_DIRNAME/$$NEW_SRC_FILE" ; \
			done ; \
			LINE_COVERAGE=`llvm-cov -gcno=./$$LCOV_BASENAME.gcno -gcda=./$$LCOV_BASENAME.gcda | grep '^[[:space:]]*[[:digit:]]\+' | wc -l`  ; \
			LINE_COVERAGE_TOTAL=`expr $$LINE_COVERAGE_TOTAL + $$LINE_COVERAGE` ; \
		done ; \
		LOC_TOTAL=0 ; \
		for LCOV_SRC in $$LCOV_SOURCES ; do \
			if [ -e $$LCOV_SRC ] ; then \
				LOC=`sloccount $$LCOV_SRC |grep "Total Physical" | sed s/^[[:alpha:],[:space:],\(,\),\=]*//` ; \
				if [ x$$LOC != x ] ; then \
					LOC_TOTAL=`expr $$LOC_TOTAL + $$LOC` ; \
				fi ; \
			fi ; \
		done ; \
		( echo -n $$LINE_COVERAGE_TOTAL > $$OUTPUT_DIR/LcovLog.txt ) ; \
		( echo -n $$LOC_TOTAL > $$OUTPUT_DIR/SLocCountLog.txt ) \
	)
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"`

%.stpklee: build
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
	@echo =================================================================
	@echo Running KLEE with STP on $* ...
	@echo =================================================================
	if [ -z "$$PROGRAM_OPTIONS" ] ; then \
		if [ $* = "dd" ]; then \
			PROGRAM_OPTIONS="${DD_OPTIONS}" ; \
		elif [ $* = "dircolors" ]; then \
			PROGRAM_OPTIONS="${DIRCOLORS_OPTIONS}" ; \
		elif [ $* = "echo" ]; then \
			PROGRAM_OPTIONS="${ECHO_OPTIONS}" ; \
		elif [ $* = "expr" ]; then \
			PROGRAM_OPTIONS="${EXPR_OPTIONS}" ; \
		elif [ $* = "mknod" ]; then \
			PROGRAM_OPTIONS="${MKNOD_OPTIONS}" ; \
		elif [ $* = "od" ]; then \
			PROGRAM_OPTIONS="${OD_OPTIONS}" ; \
		elif [ $* = "pathchk" ]; then \
			PROGRAM_OPTIONS="${PATHCHK_OPTIONS}" ; \
		elif [ $* = "printf" ]; then \
			PROGRAM_OPTIONS="${PRINTF_OPTIONS}" ; \
		else \
			PROGRAM_OPTIONS="${DEFAULT_OPTIONS}" ; \
		fi ; \
	fi ; \
	if [ -z "${OUTPUT_DIR}" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	else \
		OUTPUT_DIR="${OUTPUT_DIR}" ; \
	fi ; \
	rm -rf $$OUTPUT_DIR; \
	KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_MORE_OPTIONS}"; \
	if [ "${KLEE_COREUTILS_MORE_OPTIONS}"="" ] ; then \
		KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	PROGRAM_OPTIONS="$$PROGRAM_OPTIONS -max-fail 1" ; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_COREUTILS_BASIC_OPTIONS} $$KLEE_COREUTILS_EXTRA_OPTIONS -solver-backend=stp --environ=${CURDIR}/test.env --run-in=sandbox -output-dir=$$OUTPUT_DIR ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_OPTIONS -max-fail 1 ;
	echo -n "$$PROGRAM_OPTIONS" > $$OUTPUT_DIR/ProgramOptions.txt ; \
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	if [ -z "${OUTPUT_DIR}" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	else \
		OUTPUT_DIR="${OUTPUT_DIR}" ; \
	fi ; \
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"` ; \
	( cd ${COREUTILS_COV_DIR}/src ; \
	        for KTEST in $$OUTPUT_DIR/*.ktest ; do \
			( LD_LIBRARY_PATH=${KLEE_HOME}/lib KTEST_FILE=$$KTEST ${KLEE_REPLAY} $* $$KTEST ) ; \
		done ) ; \
	( cd ${COREUTILS_COV_DIR} ; \
		LINE_COVERAGE_TOTAL=0 ; \
		LCOV_OBJECTS=`find . -name "*.gcda"` ; \
		LCOV_SOURCES="" ; \
		for LCOV_OBJ in $$LCOV_OBJECTS ; do \
			LCOV_NAME=$${LCOV_OBJ%.*} ; \
			LCOV_BASENAME=$$(basename "$${LCOV_NAME}") ; \
			LCOV_DIRNAME=$$(dirname "$${LCOV_OBJ}") ; \
			cd ${COREUTILS_COV_DIR}/$$LCOV_DIRNAME ; \
			NEW_SRC_LIST=`llvm-cov -gcno=./$$LCOV_BASENAME.gcno -gcda=./$$LCOV_BASENAME.gcda | grep '0:Source:' | sed s/-://g | sed s/0:Source://g` ; \
			for NEW_SRC_FILE in $$NEW_SRC_LIST ; do \
				LCOV_SOURCES="$$LCOV_SOURCES ${COREUTILS_COV_DIR}/$$LCOV_DIRNAME/$$NEW_SRC_FILE" ; \
			done ; \
			LINE_COVERAGE=`llvm-cov -gcno=./$$LCOV_BASENAME.gcno -gcda=./$$LCOV_BASENAME.gcda | grep '^[[:space:]]*[[:digit:]]\+' | wc -l`  ; \
			LINE_COVERAGE_TOTAL=`expr $$LINE_COVERAGE_TOTAL + $$LINE_COVERAGE` ; \
		done ; \
		LOC_TOTAL=0 ; \
		for LCOV_SRC in $$LCOV_SOURCES ; do \
			if [ -e $$LCOV_SRC ] ; then \
				LOC=`sloccount $$LCOV_SRC |grep "Total Physical" | sed s/^[[:alpha:],[:space:],\(,\),\=]*//` ; \
				if [ x$$LOC != x ] ; then \
					LOC_TOTAL=`expr $$LOC_TOTAL + $$LOC` ; \
				fi ; \
			fi ; \
		done ; \
		( echo -n $$LINE_COVERAGE_TOTAL > $$OUTPUT_DIR/LcovLog.txt ) ; \
		( echo -n $$LOC_TOTAL > $$OUTPUT_DIR/SLocCountLog.txt ) \
	)
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"`

clean:
	rm -rf *.klee* *.tx* *.stpklee* ${EXPERIMENT_CSV} cav-${EXPERIMENT_CSV} ${LLBMC_EXPERIMENT_CSV} ${LLBMC_OUTPUT_DIR} sandbox sandbox.temps test.env

realclean: clean
	rm -rf ${COREUTILS_LLVM_DIR} ${COREUTILS_COV_DIR}

core-experiment:
	for program in ${EXPERIMENT_SET} ; \
	do \
		make $$program.klee1;    \
		make $$program.klee2;    \
		make $$program.tx1; \
		make $$program.tx2; \
		make $$program.tx3; \
		make $$program.tx4; \
		make $$program.tx5; \
		make $$program.tx6; \
	done

# This target is used for collecting data from experimental results into experiment.csv file.
${EXPERIMENT_CSV}: core-experiment
	( cd ../utils ; CC=${CC} make treecmp ) 
	echo "Directory,Program Options,klee-stats Time (s),KLEE info Elapsed (s), #instructions,#error,#completed paths,#error paths,#subsumed paths,#program exit paths,Average branching depth of completed paths,Average branching depth of subsumption paths,Average instructions of completed paths, Average instructions of subsumed paths,Icov,Bcov,llvm-cov line coverage,SLOC,Time for actual solver calls in subsumption check (ms),Number of solver calls for subsumption check,Number of solver calls for subsumption check that resulted in subsumption failure,Average table entries per subsumption checkpoint,Average solver calls per subsumption check,Number of subsumption checks,KLEE paths saved,Tracer-X new paths,KLEE paths before last Tracer-X path" >> $@; \
	for ext in .klee1 .klee2 .tx1 .tx2 .tx3 .tx4 .tx5 .tx6 ; \
	do \
		for program in ${EXPERIMENT_SET} ; \
		do \
			if [ -d $$program$$ext ]; then \
				printf "$$program$$ext," >> $@; \
				cat $$program$$ext/ProgramOptions.txt >> $@; \
				printf ", " >> $@; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f4  | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "Elapsed:" ${CURDIR}/$$program$$ext/info | cut -d' ' -f2 |  sed 's/:/ /g;' | awk '{print $$3" "$$2" "$$1}' | awk '{print $$1+$$2*60+$$3*3600}' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done: total instructions" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/'| tr -d '\n' >> $@; \
				printf ", " >> $@; \
				echo -n `ls $$program$$ext | grep err | wc -l` >> $@ ; \
				printf ", " >> $@; \
				grep "KLEE: done: completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d ', among which\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done:     error paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done:     subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done:     program exit paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "average branching depth of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "average branching depth of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "average instructions of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "average instructions of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f5 | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f6 | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				if [ -e $$program$$ext/LcovLog.txt ]; then \
					cat $$program$$ext/LcovLog.txt | tr -d '\n' >> $@; \
				fi ; \
				printf ", " >> $@; \
				if [ -e $$program$$ext/SLocCountLog.txt ]; then \
					cat ${CURDIR}/$$program$$ext/SLocCountLog.txt | tr -d '\n' >> $@; \
				fi ; \
				printf ", " >> $@; \
				grep "Time for actual solver calls in subsumption check (ms)" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\1/'| tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\2/' | tr -d ')\n' >> $@; \
				printf ", " >> $@; \
				grep "Average table entries per subsumption checkpoint" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "Average solver calls per subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done:     Number of subsumption checks" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				if [ $$ext = .tx1 -o $$ext = .tx2 -o $$ext = .tx5 -o $$ext = .tx6 ] ;  then \
					( ../utils/treecmp $$program.klee1 $$program$$ext | sed -e 's/\s/\,/g'  ) >> $@ ; \
				else \
					printf "\n" >> $@; \
				fi ; \
			fi ; \
		done ; \
	done

cav-core-experiment:
	make pr.klee7
	make pr.klee8
	make pr.klee9
	make pr.tx7
	make pr.tx8
	make pr.tx9
	make cut.klee10
	make cut.klee11
	make cut.klee12
	make cut.klee13
	make cut.tx10
	make cut.tx11
	make cut.tx12
	make cut.tx13
	make printf.klee14
	make printf.klee15
	make printf.klee16
	make printf.tx14
	make printf.tx15
	make printf.tx16
	make basename.klee17
	make basename.klee18
	make basename.klee19
	make basename.klee20
	make basename.tx17
	make basename.tx18
	make basename.tx19
	make basename.tx20
	make head.klee21
	make head.klee22
	make head.klee23
	make head.tx21
	make head.tx22
	make head.tx23
	make pathchk.klee24
	make pathchk.klee25
	make pathchk.klee26
	make pathchk.klee27
	make pathchk.klee28
	make pathchk.klee29
	make pathchk.tx24
	make pathchk.tx25
	make pathchk.tx26
	make pathchk.tx27
	make pathchk.tx28
	make pathchk.tx29

# This target is used for collecting data from experimental results into experiment.csv file.
cav-${EXPERIMENT_CSV}: cav-core-experiment
	( cd ../utils ; CC=${CC} make treecmp ) 
	echo "Directory,Program Options,klee-stats Time (s),KLEE info Elapsed (s), #instructions,#error,#completed paths,#error paths,#subsumed paths,#program exit paths,Average branching depth of completed paths,Average branching depth of subsumption paths,Average instructions of completed paths, Average instructions of subsumed paths,Icov,Bcov,llvm-cov line coverage,SLOC,Time for actual solver calls in subsumption check (ms),Number of solver calls for subsumption check,Number of solver calls for subsumption check that resulted in subsumption failure,Average table entries per subsumption checkpoint,Average solver calls per subsumption check,Number of subsumption checks,KLEE paths saved,Tracer-X new paths,KLEE paths before last Tracer-X path" >> $@; \
	for ext in .klee7 .klee8 .klee9 .klee10 .klee11 .klee12 .klee13 .klee14 .klee15 .klee16 .klee17 .klee18 .klee19 .klee20 .klee21 .klee22 .klee23 .klee24 .klee25 .klee26 .klee27 .klee28 .klee29 .tx7 .tx8 .tx9 .tx10 .tx11 .tx12 .tx13 .tx14 .tx15 .tx16 .tx17 .tx18 .tx19 .tx20 .tx21 .tx22 .tx23 .tx24 .tx25 .tx26 .tx27 .tx28 .tx29 ; \
	do \
		for program in pr cut printf basename head pathchk ; \
		do \
			if [ -d $$program$$ext ]; then \
				printf "$$program$$ext," >> $@; \
				cat $$program$$ext/ProgramOptions.txt >> $@; \
				printf ", " >> $@; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f4  | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "Elapsed:" ${CURDIR}/$$program$$ext/info | cut -d' ' -f2 |  sed 's/:/ /g;' | awk '{print $$3" "$$2" "$$1}' | awk '{print $$1+$$2*60+$$3*3600}' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done: total instructions" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/'| tr -d '\n' >> $@; \
				printf ", " >> $@; \
				echo -n `ls $$program$$ext | grep err | wc -l` >> $@ ; \
				printf ", " >> $@; \
				grep "KLEE: done: completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d ', among which\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done:     error paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done:     subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done:     program exit paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "average branching depth of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "average branching depth of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "average instructions of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "average instructions of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f5 | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f6 | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				if [ -e $$program$$ext/LcovLog.txt ]; then \
					cat $$program$$ext/LcovLog.txt | tr -d '\n' >> $@; \
				fi ; \
				printf ", " >> $@; \
				if [ -e $$program$$ext/SLocCountLog.txt ]; then \
					cat ${CURDIR}/$$program$$ext/SLocCountLog.txt | tr -d '\n' >> $@; \
				fi ; \
				printf ", " >> $@; \
				grep "Time for actual solver calls in subsumption check (ms)" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\1/'| tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\2/' | tr -d ')\n' >> $@; \
				printf ", " >> $@; \
				grep "Average table entries per subsumption checkpoint" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "Average solver calls per subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				grep "KLEE: done:     Number of subsumption checks" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> $@; \
				printf ", " >> $@; \
				if [ $$ext = .tx1 -o $$ext = .tx2 -o $$ext = .tx5 -o $$ext = .tx6 ] ;  then \
					( ../utils/treecmp $$program.klee1 $$program$$ext | sed -e 's/\s/\,/g'  ) >> $@ ; \
				else \
					printf "\n" >> $@; \
				fi ; \
			fi ; \
		done ; \
	done

# This target is used for running coreutils experiment with
# LLBMC. Arguments in PROGRAM_OPTIONS have lengths matching that of
# KLEE runs. For example, Klee runs with --sym-args 0 1 10 --sym-args
# 0 2 2 which defined in DEFAULT_OPTIONS, means coreutils programs are
# triggered with 2 short options (length 2) and 1 long option (length
# 10). This arguments example in KLEE run is translated into "xx xx
# xxxxxxxxxx".
%.llbmc :
	if [ $* = "dd" ]; then \
		PROGRAM_OPTIONS="xxxxxxxxxx xxxxxxxxxx xxxxxxxxxx" ; \
	elif [ $* = "dircolors" ]; then \
		PROGRAM_OPTIONS="xxxxxxxxxx xxxxxxxxxx xxxxxxxxxx" ; \
	elif [ $* = "echo" ]; then \
		PROGRAM_OPTIONS="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ; \
	elif [ $* = "expr" ]; then \
		PROGRAM_OPTIONS="xxx xxx xxxxxxxxxx" ; \
	elif [ $* = "mknod" ]; then \
		PROGRAM_OPTIONS="xxx xxx xxxxxxxxxx" ; \
	elif [ $* = "od" ]; then \
		PROGRAM_OPTIONS="xxxxxxxxxx xxxxxxxxxx xxxxxxxxxx" ; \
	elif [ $* = "pathchk" ]; then \
		PROGRAM_OPTIONS="x x" ; \
	elif [ $* = "printf" ]; then \
		PROGRAM_OPTIONS="xxxxxxxxxx xxxxxxxxxx xxxxxxxxxx" ; \
	else \
		PROGRAM_OPTIONS="xx xx xxxxxxxxxx" ; \
	fi ; \
	if [ ! -d ${LLBMC_OUTPUT_DIR} ]; then \
		mkdir ${LLBMC_OUTPUT_DIR}; \
	fi ; \
	${CC} -emit-llvm -c ${CFLAGS_LLBMC_COREUTILS} ${COREUTILS_SRC}/$*.c -o ${COREUTILS_SRC}/$*.bc ; \
	export PATH=${EXTRA_PATH}:$$PATH ; \
	llbmc ${LLBMC_OPTIONS} -arguments="$$PROGRAM_OPTIONS" ${COREUTILS_SRC}/$*.bc > ${LLBMC_OUTPUT_DIR}/$* ; \
	rm -rf ${COREUTILS_SRC}/$*.bc ; \

# This target is used for collecting data from coreutils LLBMC experiment into log-llbmc file.
${LLBMC_EXPERIMENT_CSV}:
	echo "Program, Time for performing transformations on LLVM IR,Time for performing logical encoding,Time for performing formula transformations,Time for running SMT solver (STP with MiniSat), Total time,Error status" >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
	for program in ${EXECUTABLE_TARGETS} ; \
	do \
		if [ -e ${LLBMC_OUTPUT_DIR}/$$program ]; then \
			printf "$$program," >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			grep "Performing transformations on LLVM IR" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing transformations on LLVM IR sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			printf ", " >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			grep "Performing logical encoding" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing logical encoding sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			printf ", " >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			grep "Performing formula transformations" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing formula transformations sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			printf ", " >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			grep "Running SMT solver (STP with MiniSat)" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Running SMT solver (STP with MiniSat) sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			printf ", " >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			awk '/[DONE]/{i++}i==5' ${LLBMC_OUTPUT_DIR}/$$program | tr -d  "sec [DONE] Result:=\n" >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			printf ", " >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			grep "Error detected." ${LLBMC_OUTPUT_DIR}/$$program | tr -d  "\n"  >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
			printf "\n" >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
		fi ; \
	done ; \
