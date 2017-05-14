# Makefile to build and run the examples using KLEE.
#
# Copyright 2016, 2017 National University of Singapore

# This is for extra KLEE options
EXTRA_OPTIONS=-interpolation-stat

# This is for the options passed onto the tested program, e.g.,
# --sym-arg
PROGRAM_OPTIONS=

# The following is for computing coverage from the test files within
# the start of the execution up to, and not including the specified
# time.  Empty means no max time set for computing coverage of test,
# so all tests will be considered in computing coverage.
SCALABILITY_COV_MAX_TIME=

TARGETS=$(patsubst %.c,%.tx,$(wildcard *.c))

# Regexp-only experiment set, with fixed "hello" string input
DEFAULT_EXPERIMENT_SET=Regexp RegexpSize8 RegexpSize9 RegexpSize10

# Regexp-only experiment set, with varied regular expression and string input sizes
DEFAULT_EXPERIMENT_SET=Regexp-6-3 Regexp-6-4 Regexp-6-5 Regexp-7-3 Regexp-7-4 Regexp-7-5 Regexp-8-3 Regexp-8-4 Regexp-8-5

# Bubble sort-only experiment set
DEFAULT_EXPERIMENT_SET=bubble_assert3 bubble_assert4 bubble_assert5 bubble_assert6 bubble_assert7 bubble_assert8 bubble_assert9 bubble_assert12 bubble_assert9_unsafe bubble_assert12_unsafe

# malloc-only experiment set
DEFAULT_EXPERIMENT_SET=malloc9 malloc18 malloc27 malloc36

# Standard experiment set
DEFAULT_EXPERIMENT_SET=bitcount16 bitcount32 bubble6 bubble9 compress cut_bytes cut_fields expint fac fermat fibcall graycode insertsort11 janne_complex lcdnum magic matrixsqrt merge multiply ns nsichneu popcount prime queens recursion Regexp sample send-more-money statemate tr tritype ud wegner

DEFAULT_EXPERIMENT_TYPE_SET=.klee1 .klee2 .tx1 .tx2 .tx3 .tx4 .tx5 .tx6 .klee11 .tx11 .tx12 .tx13 .tx14

EXPERIMENT_CSV=experiment.csv

EXPERIMENT_TIMEOUT=3600

EXPERIMENT_MEMORY=13000

# Here we use -only-output-states-covering-new by default to save disk space.
KLEE_DEFAULT_OPTIONS=-search=dfs -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new

# LLBMC options can be set here; when empty, default options will be
# used instead.
LLBMC_OPTIONS=

LLBMC_EXPERIMENT_CSV=llbmc-${EXPERIMENT_CSV}

TR_TARGETS=tr.tr0 tr_nosyscall.tr0 tr_small.tr0

EXTRA_REMOVAL=${TR_TARGETS} ${BUBBLE_TARGETS}

include ../Makefile.common

#################################################################################
# Below are special targets for special run configurations                      #
#                                                                               #
# To run all programs under specific group targets, please run:                 #
#   Make <group_target>                                                         #
#     Example:                                                                  #
#       Make tr  ==> run tr, tr_nosyscall, and tr_small                         #
#       Make bubble  ==> run bubble9, bubble12, bubble9_unsafe, bubble12_unsafe #
# To run only a specific program, please run:                                   #
#   Make <program_name>.<suffixes_group>                                        #
#     Example:                                                                  #
#       Make tr_nosyscall.tr0 (only run tr_nosyscall)                           #
#       Make bubble9.bubble0 (only run bubble9)                                 #
#################################################################################

# For running Minix tr versions
tr: ${TR_TARGETS}
	rm -rf klee-*
	rm -f $^

bubble: ${BUBBLE_TARGETS}
	rm -rf klee-*
	rm -f $^


clean: standard-clean
	rm -rf *.klee* *.tx* *.stpklee* ${EXPERIMENT_CSV} small-${EXPERIMENT_CSV} \
		${LLBMC_EXPERIMENT_CSV}

.SUFFIXES: .tr0

.bc.tr0:
	rm -rf $@ klee-*
	time ${KLEE} -solver-backend=z3 --max-time=120 -interpolation-stat -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls -output-tree $< --sym-arg 1 --sym-arg 1 --sym-stdin 2000 --max-fail 1
	rm -rf klee-*
	time ${KLEE} -solver-backend=z3 --max-time=120 -interpolation-stat -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls $< --sym-arg 2 --sym-arg 2 --sym-stdin 2000 --max-fail 1
	rm -rf klee-*
	time ${KLEE} -solver-backend=z3 --max-time=120 -interpolation-stat -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls $< --sym-arg 3 --sym-arg 3 --sym-stdin 2000 --max-fail 1
	touch $@

%.klee1 : 
	KLEE_OPTIONS="--search=dfs -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.klee2 : 
	KLEE_OPTIONS="--search=random-path --search=nurs:covnew -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tx1 : 
	KLEE_OPTIONS="--search=dfs -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx2 : 
	KLEE_OPTIONS="--search=dfs -max-subsumption-failure=3 -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx3 : 
	KLEE_OPTIONS="--search=random-path --search=nurs:covnew -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx4 : 
	KLEE_OPTIONS="--search=random-path --search=nurs:covnew -max-subsumption-failure=3 -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx5 : 
	KLEE_OPTIONS="--search=dfs -exact-address-interpolant -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx6 : 
	KLEE_OPTIONS="--search=dfs -exact-address-interpolant -max-subsumption-failure=3 -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -only-output-states-covering-new" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

# The following targets are run with -write-paths and without
# -only-output-states-covering-new for comparing tree sizes using
# utils/treecmp.c.
%.klee11 : 
	KLEE_OPTIONS="--search=dfs -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee

%.tx11 : 
	KLEE_OPTIONS="--search=dfs -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx12 : 
	KLEE_OPTIONS="--search=dfs -max-subsumption-failure=3 -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx13 : 
	KLEE_OPTIONS="--search=dfs -exact-address-interpolant -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

%.tx14 : 
	KLEE_OPTIONS="--search=dfs -exact-address-interpolant -max-subsumption-failure=3 -max-memory=${EXPERIMENT_MEMORY} -max-time=${EXPERIMENT_TIMEOUT} -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.tx

###############################################################################
# The following targets can be used for running experiments. The
# conducted experiments involved different option settings of KLEE and
# Tracer-X which can be seen in %.klee... and %.tx... targets.
###############################################################################
%.tx:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	SOLVER_FLAGS="-solver-backend=z3" OUTPUT_DIR="$$OUTPUT_DIR" make $*.klee-out

%.klee:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	SOLVER_FLAGS="-solver-backend=z3 -no-interpolation" OUTPUT_DIR="$$OUTPUT_DIR" make $*.klee-out

# The following is for running using STP, so we do 'ulimit -s
# unlimited' beforehand, as recommended in
# http://klee.github.io/build-stp/
%.stpklee:
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR=${CURDIR}/$@ ; \
	fi ; \
	ulimit -s unlimited ; \
	SOLVER_FLAGS="-solver-backend=stp" OUTPUT_DIR="$$OUTPUT_DIR" make $*.klee-out

%.klee-out:
	@KLEE_RUNTIME_DLL=${KLEE_HOME}/lib/libkleeRuntest.so.1.0 ; \
	if [ ! -e $$KLEE_RUNTIME_DLL ] ; then \
		echo "ERROR: KLEE runtime library libkleeRuntest.so.1.0 is not found: You may need to run ldconfig -n ${KLEE_HOME}/lib" ; \
		exit 1 ; \
	fi
	${CC} -emit-llvm ${CFLAGS} -c $*.c
	if [ -z "$$KLEE_MORE_OPTIONS" ] ; then \
		if [ $* = "tr" ] ; then \
			KLEE_MORE_OPTIONS="-libc=uclibc --posix-runtime -allow-external-sym-calls" ; \
		elif [ $* = "tr_nosyscall" ] ; then \
			KLEE_MORE_OPTIONS="-libc=uclibc --posix-runtime -allow-external-sym-calls" ; \
		elif [ $* = "tr_small" ] ; then \
			KLEE_MORE_OPTIONS="-libc=uclibc --posix-runtime -allow-external-sym-calls" ; \
		fi ; \
	fi ; \
	if [ -z "$$KLEE_PROGRAM_OPTIONS" ] ; then \
		if [ $* = "tr" ] ; then \
			KLEE_PROGRAM_OPTIONS="--sym-arg 2 --sym-arg 2 --sym-stdin 2000 --max-fail 1" ; \
		elif [ $* = "tr_nosyscall" ] ; then \
			KLEE_PROGRAM_OPTIONS="--sym-arg 2 --sym-arg 2 --sym-stdin 2000 --max-fail 1" ; \
		elif [ $* = "tr_small" ] ; then \
			KLEE_PROGRAM_OPTIONS="--sym-arg 2 --sym-arg 2 --sym-stdin 2000 --max-fail 1" ; \
		fi ; \
	fi ; \
	if [ -z "$$OUTPUT_DIR" ] ; then \
		OUTPUT_DIR="${CURDIR}/$@" ; \
	fi ; \
	rm -rf $$OUTPUT_DIR; \
	if [ -z "$$KLEE_OPTIONS" ] ; then \
		KLEE_OPTIONS="${KLEE_DEFAULT_OPTIONS}" ; \
	fi ; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${EXTRA_OPTIONS} $$KLEE_OPTIONS $$KLEE_MORE_OPTIONS $$SOLVER_FLAGS -output-dir=$$OUTPUT_DIR ${CURDIR}/$*.bc $$KLEE_PROGRAM_OPTIONS ; \
	echo -n "$$KLEE_PROGRAM_OPTIONS" > $$OUTPUT_DIR/ProgramOptions.txt ; \
	rm -f $*.bc; \
	if [ -e $$OUTPUT_DIR/tree.dot ]; then \
		timeout ${SVG_CREATION_TIMEOUT}s dot -Tsvg $$OUTPUT_DIR/tree.dot -o $$OUTPUT_DIR/tree.svg ; \
		if [ $$? = 124 ] ; then \
			echo WARNING: Timed out creating .svg file ; \
		fi ; \
	fi
	# Generate line coverage information
	${CURDIR}/../utils/scalabilitycov.sh "$*" "$$OUTPUT_DIR" ${SCALABILITY_COV_MAX_TIME}

core-experiment:
	if [ -z "$$EXPERIMENT_SET" ] ; then \
		EXPERIMENT_SET="${DEFAULT_EXPERIMENT_SET}" ; \
	fi ; \
	if [ -z "$$EXPERIMENT_TYPE_SET" ] ; then \
		EXPERIMENT_TYPE_SET="${DEFAULT_EXPERIMENT_TYPE_SET}" ; \
	fi ; \
	for program in $$EXPERIMENT_SET ; \
	do \
		for ext in $$EXPERIMENT_TYPE_SET ; \
		do \
			make $$program$$ext ; \
		done ; \
	done

# This target is used for collecting data from the experiment's result into experiment.csv file.
${EXPERIMENT_CSV}: core-experiment
	( cd ../utils ; CC=${CC} make treecmp ) 
	echo "Directory,Program Options,klee-stats Time (s),KLEE info Elapsed (s), #instructions,#error,#completed paths,#error paths,#subsumed paths,#program exit paths,Average branching depth of completed paths,Average branching depth of subsumption paths,Average instructions of completed paths, Average instructions of subsumed paths,Icov,Bcov,llvm-cov line coverage,LOC,Time for actual solver calls in subsumption check (ms),Number of solver calls for subsumption check,Number of solver calls for subsumption check that resulted in subsumption failure,Average table entries per subsumption checkpoint,Average solver calls per subsumption check,Number of subsumption checks,KLEE paths saved,Tracer-X and not KLEE paths,KLEE and not Tracer-X paths,KLEE paths before last Tracer-X path (-1 if unreached)" >> $@
	if [ -z "$$EXPERIMENT_SET" ] ; then \
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
				cat $$program$$ext/ProgramOptions.txt >> $@ ; \
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
				grep '^[[:space:]]*[[:digit:]]\+' $$program$$ext/$$program.cov |wc -l |tr -d '\n' >> $@; \
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

# This target is used for collecting data from LLBMC experiment into CSV file.
${LLBMC_EXPERIMENT_CSV}:
	if [ -z "$$EXPERIMENT_SET" ] ; then \
		EXPERIMENT_SET="${DEFAULT_EXPERIMENT_SET}" ; \
	fi ; \
	for program in $$EXPERIMENT_SET ; do \
		make $$program.llbmc ; \
	done ; \
	echo "Program,Timed out,Time for performing transformations on LLVM IR,Time for performing logical encoding,Time for performing formula transformations,Time for running SMT solver (STP with MiniSat), Total time,Error status" >> ${LLBMC_EXPERIMENT_CSV} ; \
	for program in $$EXPERIMENT_SET ; do \
		if [ -e ${LLBMC_OUTPUT_DIR}/$$program ]; then \
			printf "$$program," >> ${LLBMC_EXPERIMENT_CSV} ; \
			if [ -e ${LLBMC_OUTPUT_DIR}/$$program.timeout ] ; then \
				echo -n "Yes," >> ${LLBMC_EXPERIMENT_CSV} ; \
			else \
				echo -n "No," >> ${LLBMC_EXPERIMENT_CSV} ; \
			fi ; \
			grep "Performing transformations on LLVM IR" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing transformations on LLVM IR sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_EXPERIMENT_CSV} ; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV} ; \
			grep "Performing logical encoding" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing logical encoding sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_EXPERIMENT_CSV} ; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV} ; \
			grep "Performing formula transformations" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Performing formula transformations sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_EXPERIMENT_CSV} ; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV} ; \
			grep "Running SMT solver (STP with MiniSat)" ${LLBMC_OUTPUT_DIR}/$$program | tr -d 'Running SMT solver (STP with MiniSat) sec [DONE]\n' |  sed -r 's/^.{3}//' >> ${LLBMC_EXPERIMENT_CSV} ; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV} ; \
			awk '/[DONE]/{i++}i==5' ${LLBMC_OUTPUT_DIR}/$$program | tr -d  "sec [DONE] Result:=\n" >> ${LLBMC_EXPERIMENT_CSV} ; \
			printf ", " >> ${LLBMC_EXPERIMENT_CSV} ; \
			grep "Error detected." ${LLBMC_OUTPUT_DIR}/$$program | tr -d  "\n"  >> ${LLBMC_EXPERIMENT_CSV} ; \
			printf "\n" >> ${LLBMC_EXPERIMENT_CSV} ; \
		fi ; \
	done
