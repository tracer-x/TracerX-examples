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
TARGETS=[ arch base64 basename cat chcon chgrp chmod chown chroot cksum comm cp csplit cut date dd df dircolors dirname du echo env expand expr factor false fmt fold head hostid hostname id ginstall join kill link ln logname ls md5sum mkdir mkfifo mknod mktemp mv nice nl nohup od paste pathchk pinky pr printenv printf ptx pwd readlink rm rmdir runcon seq setuidgid shred shuf sleep sort split stat stty sum sync tac tail tee touch tr tsort tty uname unexpand uniq unlink uptime users wc whoami who yes 

DEFAULT_OPTIONS=--sym-args 0 1 10 --sym-args 0 2 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout
DD_OPTIONS=--sym-args 0 3 10 --sym-files 1 8 -sym-stdin 8 --sym-stdout
DIRCOLORS_OPTIONS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout
ECHO_OPTIONS=--sym-args 0 4 300 --sym-files 2 30 -sym-stdin 30 --sym-stdout
EXPR_OPTIONS=--sym-args 0 1 10 --sym-args 0 3 2 --sym-stdout
MKNOD_OPTIONS=--sym-args 0 1 10 --sym-args 0 3 2 --sym-files 1 8 -sym-stdin 8 --sym-stdout
OD_OPTIONS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout
PATHCHK_OPTIONS=--sym-args 0 1 2 --sym-args 0 1 300 --sym-files 1 8 -sym-stdin 8 --sym-stdout
PRINTF_OPTIONS=--sym-args 0 3 10 --sym-files 2 12 -sym-stdin 12 --sym-stdout

KLEE_TARGETS=$(TARGETS:=.klee)

KLEESTP_TARGETS=$(TARGETS:=.stpklee)

# Coreutils benchmark set for November 2016 experiment
EXPERIMENT_SET=cut expand join sum uniq factor comm dirname split

EXPERIMENT_CSV=experiment.csv

EXPERIMENT_TIMEOUT=3600.

# From http://klee.github.io/docs/coreutils-experiments/
# with --search=random-path and --max-time=3600. excluded to be
# specified via KLEE_COREUTILS_MORE_OPTIONS or
# KLEE_COREUTILS_DEFAULT_OPTIONS (see below).
KLEE_COREUTILS_BASIC_OPTIONS=--simplify-sym-indices --write-cvcs --write-cov --output-module \
	--max-memory=1000 --disable-inlining --optimize --use-forked-solver \
	--use-cex-cache --libc=uclibc --posix-runtime \
	--allow-external-sym-calls --only-output-states-covering-new \
	--max-sym-array-size=4096 --max-instruction-time=30. \
	--watchdog --max-memory-inhibit=false --max-static-fork-pct=1 \
	--max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal \
	--randomize-fork --search=nurs:covnew \
	--use-batching-search --batch-instructions=10000

# Comment this out if the above options are preferred
KLEE_COREUTILS_DEFAULT_OPTIONS=--search=dfs -max-time=${EXPERIMENT_TIMEOUT}

LLBMC_EXPERIMENT_CSV=llbmc-${EXPERIMENT_CSV}

KLEE_TARGETS1=$(EXPERIMENT_SET:=.klee1)
KLEE_TARGETS2=$(EXPERIMENT_SET:=.klee2)
TRACERX_TARGETS1=$(EXPERIMENT_SET:=.tracerx1)
TRACERX_TARGETS2=$(EXPERIMENT_SET:=.tracerx2)
TRACERX_TARGETS3=$(EXPERIMENT_SET:=.tracerx3)
TRACERX_TARGETS4=$(EXPERIMENT_SET:=.tracerx4)

# The first target (default)
all: ${KLEE_TARGETS} ${KLEESTP_TARGETS}

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
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -solver-backend=z3 -no-interpolation -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.klee2 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -solver-backend=z3 -no-interpolation -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tracerx1 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -solver-backend=z3 -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tracerx2 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-subsumption-failure=3 -solver-backend=z3 -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tracerx3 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -solver-backend=z3 -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tracerx4 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -max-subsumption-failure=3 -solver-backend=z3 -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

# This target can be used for running experiments. The conducted
# experiments involved different option settings of KLEE and Tracer-X
# which can be seen in %.klee1, %.klee2, %.tracerx1, %.tracerx2,
# %.tracerx3, and %.tracerx4 target.
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
	@echo Running Tracer-X on $* ...
	@echo =================================================================
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
	rm -rf $@; \
	KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_MORE_OPTIONS}"; \
	if [ "${KLEE_COREUTILS_MORE_OPTIONS}"="" ] ; then \
		KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} -interpolation-stat ${KLEE_COREUTILS_BASIC_OPTIONS} $$KLEE_COREUTILS_EXTRA_OPTIONS -solver-backend=z3 --environ=${CURDIR}/test.env --run-in=${CURDIR}/sandbox -output-dir=${OUTPUT_DIR} ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_OPTIONS -max-fail 1 ; \
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Create SVGs from tree.dot file if any ...
	@echo =================================================================
	if [ -e ${OUTPUT_DIR}/tree.dot ]; then \
		dot -Tsvg ${OUTPUT_DIR}/tree.dot -o ${OUTPUT_DIR}/$*.svg ; \
	fi
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"` ; \
	( cd ${COREUTILS_COV_DIR}/src ; \
	        for KTEST in ${OUTPUT_DIR}/*.ktest ; do \
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
		( echo -n $$LINE_COVERAGE_TOTAL > ${OUTPUT_DIR}/LcovLog.txt ) ; \
		( echo -n $$LOC_TOTAL > ${OUTPUT_DIR}/SLocCountLog.txt ) \
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
	rm -rf $@; \
	KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_MORE_OPTIONS}"; \
	if [ "${KLEE_COREUTILS_MORE_OPTIONS}"="" ] ; then \
		KLEE_COREUTILS_EXTRA_OPTIONS="${KLEE_COREUTILS_DEFAULT_OPTIONS}" ; \
	fi ; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_COREUTILS_BASIC_OPTIONS} $$KLEE_COREUTILS_EXTRA_OPTIONS -solver-backend=stp --environ=${CURDIR}/test.env --run-in=sandbox -output-dir=${CURDIR}/$@ ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_OPTIONS -max-fail 1 ;
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"` ; \
	( cd ${COREUTILS_COV_DIR}/src ; \
	        for KTEST in ${OUTPUT_DIR}/*.ktest ; do \
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
		( echo -n $$LINE_COVERAGE_TOTAL > ${OUTPUT_DIR}/LcovLog.txt ) ; \
		( echo -n $$LOC_TOTAL > ${OUTPUT_DIR}/SLocCountLog.txt ) \
	)
	rm -f `find ${COREUTILS_COV_DIR} -name "*.gcda"`

clean:
	rm -rf ${KLEE_TARGETS} ${KLEE_TARGETS1} ${KLEE_TARGETS2} ${KLEE_TARGETS3} ${KLEE_TARGETS4} ${TRACERX_TARGETS1} ${TRACERX_TARGETS2} ${TRACERX_TARGETS3} ${TRACERX_TARGETS4} ${EXPERIMENT_CSV} ${LLBMC_EXPERIMENT_CSV} ${KLEESTP_TARGETS} ${LLBMC_OUTPUT_DIR} sandbox sandbox.temps test.env

realclean: clean
	rm -rf ${COREUTILS_LLVM_DIR} ${COREUTILS_COV_DIR}

core-experiment:
	for program in ${EXPERIMENT_SET} ; \
	do \
		make $$program.klee1;    \
		make $$program.klee2;    \
		make $$program.tracerx1; \
		make $$program.tracerx2; \
		make $$program.tracerx3; \
		make $$program.tracerx4; \
	done

# This target is used for collecting data from experimental results into experiment.csv file.
${EXPERIMENT_CSV}: core-experiment
	( cd ../utils ; CC=${CC} make treecmp ) 
	echo "Directory,Time, #instructions,#error,#completed paths,#error paths,#subsumed paths,#program exit paths,Average branching depth of completed paths,Average branching depth of subsumption paths,Average instructions of completed paths, Average instructions of subsumed paths,Icov,Bcov,llvm-cov line coverage,SLOC,Time for actual solver calls in subsumption check (ms),Number of solver calls for subsumption check,Number of solver calls for subsumption check that resulted in subsumption failure,Average table entries per subsumption checkpoint,Average solver calls per subsumption check,Number of subsumption checks,KLEE paths saved,Tracer-X new paths,KLEE paths before last Tracer-X path" >> ${EXPERIMENT_CSV}; \
	for ext in .klee1 .klee2 .tracerx1 .tracerx2 .tracerx3 .tracerx4; \
	do \
		for program in ${EXPERIMENT_SET} ; \
		do \
			if [ -d $$program$$ext ]; then \
				printf "$$program$$ext," >> ${EXPERIMENT_CSV}; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f4  | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "KLEE: done: total instructions" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/'| tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				echo -n `ls $$program$$ext | grep err | wc -l` >> ${EXPERIMENT_CSV} ; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "KLEE: done: completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d ', among which\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "KLEE: done:     error paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "KLEE: done:     subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "KLEE: done:     program exit paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "average branching depth of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "average branching depth of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "average instructions of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "average instructions of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f5 | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f6 | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				if [ -e $$program$$ext/LcovLog.txt ]; then \
					cat $$program$$ext/LcovLog.txt | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				fi ; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				if [ -e $$program$$ext/SLocCountLog.txt ]; then \
					cat ${CURDIR}/$$program$$ext/SLocCountLog.txt | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				fi ; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "Time for actual solver calls in subsumption check (ms)" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\1/'| tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\2/' | tr -d ')\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "Average table entries per subsumption checkpoint" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "Average solver calls per subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				grep "KLEE: done:     Number of subsumption checks" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
			fi ; \
			if [ $$ext = .tracerx1 -o $$ext = .tracerx2 ] ;  then \
				( ../utils/treecmp $$program.klee1 $$program$$ext | sed -e 's/\s/\,/g'  ) >> ${EXPERIMENT_CSV} ; \
			else \
				printf "\n" >> ${EXPERIMENT_CSV}; \
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
	for program in ${TARGETS} ; \
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
