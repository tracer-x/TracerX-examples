# Makefile to build and run the examples using KLEE.
#
# Copyright 2016, 2017 National University of Singapore
#
# Symbolic arguments for testing coreutils is following
# http://klee.github.io/docs/coreutils-experiments/

COREUTILS_DIR=${CURDIR}/coreutils-6.10
COREUTILS_LLVM_DIR=${COREUTILS_DIR}/obj-llvm
COREUTILS_COV_DIR=${COREUTILS_DIR}/obj-cov
COREUTILS_NOLINK_DIR=${COREUTILS_DIR}/obj-nolink

# The following is for computing coverage from the test files within
# the start of the execution up to, and not including the specified
# time.  Empty means no max time set for computing coverage of test,
# so all tests will be considered in computing coverage.
COREUTILS_COV_MAX_TIME=

CFLAGS_LLBMC_COREUTILS=-g -I${COREUTILS_LLVM_DIR}/lib -I${COREUTILS_DIR}/src -I${COREUTILS_DIR}/lib
LLBMC_OPTIONS=--ignore-missing-function-bodies -function-name=main -max-loop-iterations=5 -max-function-call-depth=10

BASH=/bin/bash

LESS_TARGETS=base64.tx basename.tx cat.tx chcon.tx chgrp.tx chmod.tx chown.tx chroot.tx cksum.tx comm.tx cp.tx csplit.tx cut.tx date.tx dd.tx df.tx dircolors.tx dirname.tx du.tx echo.tx env.tx expand.tx expr.tx factor.tx false.tx fmt.tx fold.tx head.tx hostid.tx hostname.tx id.tx join.tx kill.tx link.tx ln.tx logname.tx ls.tx mkdir.tx mkfifo.tx mknod.tx mktemp.tx mv.tx nice.tx nl.tx nohup.tx od.tx paste.tx pathchk.tx pinky.tx pr.tx printenv.tx printf.tx ptx.tx pwd.tx readlink.tx rm.tx rmdir.tx runcon.tx seq.tx setuidgid.tx shred.tx shuf.tx sleep.tx sort.tx split.tx stat.tx stty.tx sum.tx sync.tx tac.tx tail.tx tee.tx touch.tx tr.tx tsort.tx tty.tx uname.tx unexpand.tx uniq.tx unlink.tx uptime.tx users.tx wc.tx whoami.tx who.tx yes.tx

# From http://klee.github.io/docs/coreutils-experiments/
TARGETS=[.tx arch.tx md5sum.tx ginstall.tx ${LESS_TARGETS}

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
DEFAULT_EXPERIMENT_SET=comm cut dirname expand factor join split sum uniq

DEFAULT_EXPERIMENT_TYPE_SET=.klee1 .klee2 .tx1 .tx2 .tx3 .tx4 .tx5 .tx6 .klee11 .tx11 .tx12 .tx13 .tx14

EXPERIMENT_CSV=experiment.csv

EXPERIMENT_TIMEOUT=3600

EXPERIMENT_MEMORY=13000

# From http://klee.github.io/docs/coreutils-experiments/ with
# --search, --max-time, and --max-memory excluded, to be defined in
# the targets. These we originally --max-time=3600. and
# --max-memory=1000, respectively.
KLEE_COREUTILS_BASIC_OPTIONS=--simplify-sym-indices --write-cvcs --write-cov --output-module \
	--disable-inlining --optimize --use-forked-solver \
	--use-cex-cache --posix-runtime \
	--allow-external-sym-calls \
	--max-sym-array-size=4096 --max-instruction-time=30. \
	--watchdog --max-memory-inhibit=false --max-static-fork-pct=1 \
	--max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal \
	--randomize-fork \
	--use-batching-search --batch-instructions=10000

# The defaults from http://klee.github.io/docs/coreutils-experiments/
KLEE_COREUTILS_DEFAULT_OPTIONS=--search=random-path --search=nurs:covnew -only-output-states-covering-new

LLBMC_EXPERIMENT_CSV=llbmc-${EXPERIMENT_CSV}

# The first target (default)
all: ${TARGETS} ${KLEE_TARGETS} ${STPKLEE_TARGETS}

include ../Makefile.common

build: ${COREUTILS_LLVM_DIR} ${COREUTILS_COV_DIR} test.env build-nolink

build-nolink: ${COREUTILS_NOLINK_DIR}

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

${COREUTILS_NOLINK_DIR}:
	@echo =================================================================
	@echo Building Coreutils with only the main files
	@echo =================================================================
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/x86_64-linux-gnu
	rm -rf ${COREUTILS_NOLINK_DIR}	
	mkdir ${COREUTILS_NOLINK_DIR}
	( cd ${COREUTILS_NOLINK_DIR}; \
		for program in ${LESS_TARGETS} ; do \
			PROGRAM_NOEXT="$${program%.*}" ; \
			${CC} -emit-llvm -c ${CFLAGS_LLBMC_COREUTILS} ${COREUTILS_DIR}/src/$$PROGRAM_NOEXT.c -o $$PROGRAM_NOEXT.bc ; \
		done \
	)

%.klee1 : 
	KLEE_COREUTILS_OPTIONS="--search=dfs -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.klee2 : 
	KLEE_COREUTILS_OPTIONS="--search=random-path --search=nurs:covnew -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tx1 : 
	KLEE_COREUTILS_OPTIONS="--search=dfs -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx2 : 
	KLEE_COREUTILS_OPTIONS="--search=dfs -max-subsumption-failure=3 -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx3 : 
	KLEE_COREUTILS_OPTIONS="--search=random-path --search=nurs:covnew -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx4 : 
	KLEE_COREUTILS_OPTIONS="--search=random-path --search=nurs:covnew -max-subsumption-failure=3 -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx5 : 
	KLEE_COREUTILS_OPTIONS="--search=dfs -exact-address-interpolant -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx6 : 
	KLEE_COREUTILS_OPTIONS="--search=dfs -max-subsumption-failure=3 -exact-address-interpolant -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

# The following targets are run with -write-paths and without
# -only-output-states-covering-new for comparing tree sizes using
# utils/treecmp.c.
%.klee11 : 
	KLEE_COREUTILS_OPTIONS="--search=dfs -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tx11 :
	KLEE_COREUTILS_OPTIONS="--search=dfs -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tx12 :
	KLEE_COREUTILS_OPTIONS="--search=dfs -max-subsumption-failure=3 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx13 : 
	KLEE_COREUTILS_OPTIONS="--search=dfs -exact-address-interpolant -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx14 : 
	KLEE_COREUTILS_OPTIONS="--search=dfs -max-subsumption-failure=3 -exact-address-interpolant -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

###############################################################################
# The following targets can be used for running experiments. The
# conducted experiments involved different option settings of KLEE and
# Tracer-X which can be seen in %.klee... and %.tx... targets.
###############################################################################
%.tx:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	if [ -z "$$KLEE_COREUTILS_OPTIONS" ] ; then \
		KLEE_COREUTILS_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	KLEE_COREUTILS_OPTIONS="$$KLEE_COREUTILS_OPTIONS --libc=uclibc --max-time=${EXPERIMENT_TIMEOUT} --max-memory=${EXPERIMENT_MEMORY}" SOLVER_FLAGS="-solver-backend=z3" OUTPUT_DIR=$$OUTPUT_DIR BITCODE_DIR=${COREUTILS_LLVM_DIR}/src make $*.klee-out

%.klee:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	if [ -z "$$KLEE_COREUTILS_OPTIONS" ] ; then \
		KLEE_COREUTILS_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	KLEE_COREUTILS_OPTIONS="$$KLEE_COREUTILS_OPTIONS --libc=uclibc --max-time=${EXPERIMENT_TIMEOUT} --max-memory=${EXPERIMENT_MEMORY}" SOLVER_FLAGS="-solver-backend=z3 -no-interpolation" OUTPUT_DIR=$$OUTPUT_DIR BITCODE_DIR=${COREUTILS_LLVM_DIR}/src make $*.klee-out

%.stpklee:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	if [ -z "$$KLEE_COREUTILS_OPTIONS" ] ; then \
		KLEE_COREUTILS_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	KLEE_COREUTILS_OPTIONS="$$KLEE_COREUTILS_OPTIONS --libc=uclibc --max-time=${EXPERIMENT_TIMEOUT} --max-memory=${EXPERIMENT_MEMORY}" SOLVER_FLAGS="-solver-backend=stp" OUTPUT_DIR=$$OUTPUT_DIR BITCODE_DIR=${COREUTILS_LLVM_DIR}/src make $*.klee-out

# These are for the no-linking runs, without linking with uclibc
%.tx-nolink:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	if [ -z "$$KLEE_COREUTILS_OPTIONS" ] ; then \
		KLEE_COREUTILS_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	KLEE_COREUTILS_OPTIONS="--search=dfs --max-time=${EXPERIMENT_TIMEOUT} --max-memory=${EXPERIMENT_MEMORY}" SOLVER_FLAGS="-solver-backend=z3" OUTPUT_DIR=$$OUTPUT_DIR BITCODE_DIR=${COREUTILS_NOLINK_DIR} make $*.klee-out

%.klee-nolink:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	if [ -z "$$KLEE_COREUTILS_OPTIONS" ] ; then \
		KLEE_COREUTILS_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	KLEE_COREUTILS_OPTIONS="--search=dfs --max-time=${EXPERIMENT_TIMEOUT} --max-memory=${EXPERIMENT_MEMORY}" SOLVER_FLAGS="-solver-backend=z3 -no-interpolation" OUTPUT_DIR=$$OUTPUT_DIR BITCODE_DIR=${COREUTILS_NOLINK_DIR} make $*.klee-out

%.stpklee-nolink:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	if [ -z "$$KLEE_COREUTILS_OPTIONS" ] ; then \
		KLEE_COREUTILS_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	KLEE_COREUTILS_OPTIONS="--search=dfs --max-time=${EXPERIMENT_TIMEOUT} --max-memory=${EXPERIMENT_MEMORY}" SOLVER_FLAGS="-solver-backend=stp" OUTPUT_DIR=$$OUTPUT_DIR BITCODE_DIR=${COREUTILS_NOLINK_DIR} make $*.klee-out

%.klee-out: build
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
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	fi ; \
	rm -rf $$OUTPUT_DIR; \
	KLEE_COREUTILS_EXTRA_OPTIONS="$$KLEE_COREUTILS_OPTIONS"; \
	if [ -z "$$KLEE_COREUTILS_OPTIONS" ] ; then \
		KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	PROGRAM_OPTIONS="$$PROGRAM_OPTIONS -max-fail 1" ; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_COREUTILS_BASIC_OPTIONS} $$KLEE_COREUTILS_EXTRA_OPTIONS $$SOLVER_FLAGS --environ=${CURDIR}/test.env --run-in=sandbox -output-dir=$$OUTPUT_DIR $$BITCODE_DIR/$*.bc $$PROGRAM_OPTIONS -max-fail 1 ; \
	echo -n "$$PROGRAM_OPTIONS" > $$OUTPUT_DIR/ProgramOptions.txt ; \
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	${CURDIR}/../utils/coreutilscov.sh "$*" "$$OUTPUT_DIR" ${COREUTILS_COV_MAX_TIME}
	GCDA_FILES=`find /home/dcsandr/software/klee-examples/coreutils/coreutils-6.10/obj-cov -name "*.gcda"` ; \
	if [ ! -z "$$GCDA_FILES" ] ; then \
		rm -f $$GCDA_FILES ; \
	fi

clean:
	rm -rf *.klee* *.tx* *.stpklee* *.klee-nolink *.tx-nolink *.stpklee-nolink *.klee-out ${EXPERIMENT_CSV} small-${EXPERIMENT_CSV} ${EXPERIMENT_CSV}.only small-${EXPERIMENT_CSV}.only ${LLBMC_EXPERIMENT_CSV} ${LLBMC_OUTPUT_DIR} sandbox sandbox.temps test.env

realclean: clean
	rm -rf ${COREUTILS_LLVM_DIR} ${COREUTILS_COV_DIR} ${COREUTILS_NOLINK_DIR}

core-experiment:
	if [ -z "$$EXPERIMENT_SET" ]  ; then \
		EXPERIMENT_SET="${DEFAULT_EXPERIMENT_SET}" ; \
	fi ; \
	if [ -z "$$EXPERIMENT_TYPE_SET" ] ; then \
		EXPERIMENT_TYPE_SET="${DEFAULT_EXPERIMENT_TYPE_SET}" ; \
	fi ; \
	for program in $$EXPERIMENT_SET ; \
	do \
		for ext in $$EXPERIMENT_TYPE_SET ; \
		do \
			make $$program$$ext ;    \
		done ; \
	done

${EXPERIMENT_CSV}.only:
	( cd ../utils ; CC=${CC} make treecmp ) 
	echo "Directory,Program Options,klee-stats Time (s),KLEE info Elapsed (s), #instructions,#error,#completed paths,#error paths,#subsumed paths,#program exit paths,Average branching depth of completed paths,Average branching depth of subsumption paths,Average instructions of completed paths, Average instructions of subsumed paths,Icov,Bcov,llvm-cov line coverage,LOC,Time for actual solver calls in subsumption check (ms),Number of solver calls for subsumption check,Number of solver calls for subsumption check that resulted in subsumption failure,Average table entries per subsumption checkpoint,Average solver calls per subsumption check,Number of subsumption checks,KLEE paths saved,Tracer-X and not KLEE paths,KLEE and not Tracer-X paths,KLEE paths before last Tracer-X path (-1 if unreached)" >> $@
	if [ -z "$$EXPERIMENT_SET" ]  ; then \
		EXPERIMENT_SET="${DEFAULT_EXPERIMENT_SET}" ; \
	fi ; \
	if [ -z "$$EXPERIMENT_TYPE_SET" ] ; then \
		EXPERIMENT_TYPE_SET="${DEFAULT_EXPERIMENT_TYPE_SET}" ; \
	fi ; \
	for ext in $$EXPERIMENT_TYPE_SET ; \
	do \
		for program in $$EXPERIMENT_SET ; \
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
				if [ $$ext = .tx11 -o $$ext = .tx12 -o $$ext = .tx13 -o $$ext = .tx14 ] ;  then \
					( ../utils/treecmp $$program.klee11 $$program$$ext | sed -e 's/\s/\,/g'  ) >> $@ ; \
				else \
					printf "\n" >> $@; \
				fi ; \
			fi ; \
		done ; \
	done
	rm -f small-$@
	cut --delimiter=, --fields="1,3,5-10,15-18,25-" $@ > small-$@

# This target is used for collecting data from experimental results
# into experiment.csv and smaller small-experiment.csv with less
# columns.
${EXPERIMENT_CSV}: core-experiment
	make ${EXPERIMENT_CSV}.only
	mv ${EXPERIMENT_CSV}.only ${EXPERIMENT_CSV}
	if [ -e small-${EXPERIMENT_CSV}.only ] ; then \
		rm -f small-${EXPERIMENT_CSV} ; \
		mv small-${EXPERIMENT_CSV}.only small-${EXPERIMENT_CSV} ; \
	fi

# This target is used for running coreutils experiment with
# LLBMC. Arguments in PROGRAM_OPTIONS have lengths matching that of
# KLEE runs. For example, Klee runs with --sym-args 0 1 10 --sym-args
# 0 2 2 which defined in DEFAULT_OPTIONS, means coreutils programs are
# triggered with 2 short options (length 2) and 1 long option (length
# 10). This arguments example in KLEE run is translated into "xx xx
# xxxxxxxxxx".
#
# Note that we use the bitcode of the main function without linking
# with the rest of the libraries, including libc. This is because
# LLBMC cannot handle e.g., variadic functions, which can be found in
# libraries.
%.llbmc : build-nolink
	( \
		if [ -z "$$PROGRAM_OPTIONS" ] ; then \
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
		fi ; \
		if [ -z "$$LLBMC_OUTPUT_DIR" ]; then \
			LLBMC_OUTPUT_DIR=${LLBMC_OUTPUT_DIR} ; \
		fi ; \
		if [ ! -d "$$LLBMC_OUTPUT_DIR" ]; then \
			mkdir "$$LLBMC_OUTPUT_DIR" ; \
		fi ; \
		if [ -z "${LLBMC_OPTIONS}" ] ; then \
			LLBMC_OPTIONS="${LLBMC_DEFAULT_OPTIONS}" ; \
		else \
			LLBMC_OPTIONS="${LLBMC_OPTIONS}" ; \
		fi ; \
		if [ -z "${EXPERIMENT_TIMEOUT}" ] ; then \
			LLBMC_TIMEOUT="${LLBMC_DEFAULT_TIMEOUT}" ; \
		else \
			LLBMC_TIMEOUT="${EXPERIMENT_TIMEOUT}" ; \
		fi ; \
		PATH=${EXTRA_PATH}:$$PATH timeout $$LLBMC_TIMEOUT llbmc $$LLBMC_OPTIONS -arguments="$$PROGRAM_OPTIONS" ${COREUTILS_NOLINK_DIR}/$*.bc > "$$LLBMC_OUTPUT_DIR"/$* ; \
                if [ $$? = "124" ] ; then \
                        touch $$LLBMC_OUTPUT_DIR/$*.timeout ; \
                fi \
	)

llbmc-core-experiment:
	if [ -z "$$EXPERIMENT_SET" ]  ; then \
		EXPERIMENT_SET="${DEFAULT_EXPERIMENT_SET}" ; \
	fi ; \
	for program in $$EXPERIMENT_SET ; do \
		( \
			make $$program.tx-nolink ; \
			make $$program.klee-nolink ; \
			make $$program.stpklee-nolink ; \
			make $$program.llbmc \
		) ; \
	done

# This target is used for collecting data from coreutils LLBMC
# experiment into ${LLBMC_EXPERIMENT_CSV} file.  It will create both
# ${LLBMC_EXPERIMENT_CSV} and ${EXPERIMENT_CSV}, the second containing
# data of Tracer-X and KLEE runs on the main function bitcode only,
# for comparison to LLBMC.
${LLBMC_EXPERIMENT_CSV}: llbmc-core-experiment
	if [ -z "$$EXPERIMENT_SET" ] ; then \
		EXPERIMENT_SET=$(subst .tx,,${LESS_TARGETS}) ; \
	fi ; \
	make ${LLBMC_EXPERIMENT_CSV}.only ; \
	EXPERIMENT_SET="$$EXPERIMENT_SET" EXPERIMENT_TYPE_SET=".tx-nolink .klee-nolink .stpkee-nolink" make ${EXPERIMENT_CSV}.only

${LLBMC_EXPERIMENT_CSV}.only: 
	echo "Program,Timed out,Time for performing transformations on LLVM IR,Time for performing logical encoding,Time for performing formula transformations,Time for running SMT solver (STP with MiniSat), Total time,Error status" >> ${LLBMC_EXPERIMENT_CSV}
	if [ -z "$$EXPERIMENT_SET" ] ; then \
		EXPERIMENT_SET=$(subst .tx,,${LESS_TARGETS}) ; \
	fi ; \
	for program in $$EXPERIMENT_SET ; \
	do \
		if [ -e ${LLBMC_OUTPUT_DIR}/$$program ]; then \
			printf "$$program," >> ${LLBMC_EXPERIMENT_CSV}; \
                        if [ -e ${LLBMC_OUTPUT_DIR}/$$program.timeout ] ; then \
                                echo -n "Yes," >> ${LLBMC_EXPERIMENT_CSV} ; \
                        else \
                                echo -n "No," >> ${LLBMC_EXPERIMENT_CSV} ; \
                        fi ; \
			grep "Performing transformations on LLVM IR" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing transformations on LLVM IR sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_EXPERIMENT_CSV}; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV}; \
			grep "Performing logical encoding" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing logical encoding sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_EXPERIMENT_CSV}; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV}; \
			grep "Performing formula transformations" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing formula transformations sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_EXPERIMENT_CSV}; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV}; \
			grep "Running SMT solver (STP with MiniSat)" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Running SMT solver (STP with MiniSat) sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_EXPERIMENT_CSV}; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV}; \
			awk '/[DONE]/{i++}i==5' ${LLBMC_OUTPUT_DIR}/$$program | tr -d  "sec [DONE] Result:=\n" >> ${LLBMC_EXPERIMENT_CSV}; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV}; \
			grep "Error detected." ${LLBMC_OUTPUT_DIR}/$$program | tr -d  "\n"  >> ${LLBMC_EXPERIMENT_CSV}; \
			printf "\n" >> ${LLBMC_EXPERIMENT_CSV}; \
		fi ; \
	done
