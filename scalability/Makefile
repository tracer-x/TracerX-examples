# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore

# This is for extra KLEE options
EXTRA_OPTIONS=-interpolation-stat

# This is for the options passed onto the tested program, e.g.,
# --sym-arg
PROGRAM_OPTIONS=

# We remove bubble_llbmc.klee from KLEE targets, as it
# is to be run with LLBMC
TARGETS=$(subst bubble_llbmc.klee,,$(patsubst %.c,%.klee,$(wildcard *.c)))

EXPERIMENT_SET=Regexp bubble9 adpcm bs cnt compress edn expint fac fibcall insertsort janne_complex lcdnum ludcmp merge ns nsichneu prime recursion sample statemate tr tritype ud

EXPERIMENT_CSV=experiment.csv

KLEE_TARGETS1=$(EXPERIMENT_SET:=.klee1)
KLEE_TARGETS2=$(EXPERIMENT_SET:=.klee2)
TRACERX_TARGETS1=$(EXPERIMENT_SET:=.tracerx1)
TRACERX_TARGETS2=$(EXPERIMENT_SET:=.tracerx2)
TRACERX_TARGETS3=$(EXPERIMENT_SET:=.tracerx3)
TRACERX_TARGETS4=$(EXPERIMENT_SET:=.tracerx4)

LLBMC=${HOME}/software/llbmc-2013.1-Linux_64
LLBMC_OUTPUT_DIR=${CURDIR}/LLBMC_OUTPUT
LLBMC_OPTIONS=--ignore-missing-function-bodies -function-name=main -max-loop-iterations=5 -max-function-call-depth=10

LLBMC_EXPERIMENT_CSV=${LLBMC_OUTPUT_DIR}/${EXPERIMENT_CSV}

TR_TARGETS=tr.tr0 tr_nosyscall.tr0 tr_small.tr0
BUBBLE_TARGETS=bubble9.bubble0 bubble12.bubble0 bubble9_unsafe.bubble0 bubble12_unsafe.bubble0

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

bubble_llbmc: bubble_llbmc.c
	${CC} -c -g -emit-llvm -I${LLBMC}/examples bubble_llbmc.c -o bubble_llbmc.o
	llbmc -max-loop-iterations=10 bubble_llbmc.o

# For running Minix tr versions
tr: ${TR_TARGETS}
	rm -rf klee-*
	rm -f $^

bubble: ${BUBBLE_TARGETS}
	rm -rf klee-*
	rm -f $^


clean: standard-clean
	rm -rf ${KLEE_TARGETS1} ${KLEE_TARGETS2} ${KLEE_TARGETS3} ${KLEE_TARGETS4} ${TRACERX_TARGETS1} ${TRACERX_TARGETS2} ${TRACERX_TARGETS3} ${TRACERX_TARGETS4} ${EXPERIMENT_CSV}

.SUFFIXES: .tr0 .bubble0

.bc.tr0:
	rm -rf $@ klee-*
	time ${KLEE} -solver-backend=z3 --max-time=120 -interpolation-stat -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls -output-tree $< --sym-arg 1 --sym-arg 1 --sym-stdin 2000 --max-fail 1
	rm -rf klee-*
	time ${KLEE} -solver-backend=z3 --max-time=120 -interpolation-stat -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls $< --sym-arg 2 --sym-arg 2 --sym-stdin 2000 --max-fail 1
	rm -rf klee-*
	time ${KLEE} -solver-backend=z3 --max-time=120 -interpolation-stat -libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls $< --sym-arg 3 --sym-arg 3 --sym-stdin 2000 --max-fail 1
	touch $@

.bc.bubble0:
	rm -rf $@ klee-*
	time ${KLEE} -solver-backend=z3 -max-time=120 -interpolation-stat --only-output-states-covering-new -output-tree -output-dir=$@ $<
	opt -analyze -dot-cfg $<
	mv *.dot $@
	# Create SVGs from *.dot files
	for DOTFILE in $@/*.dot ; do \
		SVGFILE=`echo -n $$DOTFILE | sed -e s/\.dot/\.svg/ -` ; \
		dot -Tsvg $$DOTFILE -o $$SVGFILE ; \
	done
	touch $@

%.klee1 : 
	KLEE_OPTIONS="--search=dfs -no-interpolation -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-experiment

%.klee2 : 
	KLEE_OPTIONS="--search=random-path --search=nurs:covnew -no-interpolation -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-experiment

%.tracerx1 : 
	KLEE_OPTIONS="--search=dfs -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-experiment

%.tracerx2 : 
	KLEE_OPTIONS="--search=dfs -max-subsumption-failure=3 -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-experiment

%.tracerx3 : 
	KLEE_OPTIONS="--search=random-path --search=nurs:covnew -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-experiment

%.tracerx4 : 
	KLEE_OPTIONS="--search=random-path --search=nurs:covnew -max-subsumption-failure=3 -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-experiment

# This target is used for running experiments. The conducted experiments involved different option settings of KLEE and Tracer-X which
# can be seen in %.klee1, %.klee2, %.tracerx1, %.tracerx2, %.tracerx3, and %.tracerx4 target.
%.klee-experiment: 
	${CC} -emit-llvm ${CFLAGS} -c $*.c
	unset KLEE_MORE_OPTIONS ; \
	unset KLEE_PROGRAM_OPTIONS ; \
	if [ $* = "Regexp" ] ; then \
		KLEE_MORE_OPTIONS="--only-output-states-covering-new" ; \
	elif [ $* = "tr" ] ; then \
		KLEE_MORE_OPTIONS="-libc=uclibc --posix-runtime -only-output-states-covering-new -allow-external-sym-calls" ; \
		KLEE_PROGRAM_OPTIONS="--sym-arg 2 --sym-arg 2 --sym-stdin 2000 --max-fail 1" ; \
	fi ; \
	rm -rf $@; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} -interpolation-stat ${KLEE_OPTIONS} $$KLEE_MORE_OPTIONS -output-dir=${OUTPUT_DIR} ${CURDIR}/$*.bc $$KLEE_PROGRAM_OPTIONS ; \
	rm -f $*.bc; \
	if [ -e ${OUTPUT_DIR}/tree.dot ]; then \
		dot -Tsvg ${OUTPUT_DIR}/tree.dot -o ${OUTPUT_DIR}/$*.svg ; \
	fi
	sloccount $*.c > ${OUTPUT_DIR}/SLocCountLog.txt 2>&1
	# Generate line coverage information
	rm -rf $* $*.gcno $*.gcda
	${CC} ${CFLAGS} -fprofile-arcs -ftest-coverage ${LDFLAGS} $*.c -o $*
	for KTEST in ${OUTPUT_DIR}/*.ktest ; do \
		( LD_LIBRARY_PATH=${KLEE_HOME}/lib KTEST_FILE=$$KTEST ${KLEE_REPLAY} $* $$KTEST ) ; \
	done	
	llvm-cov -gcno=$*.gcno -gcda=$*.gcda > ${OUTPUT_DIR}/$*.cov
	@echo Line coverage = `grep '^[[:space:]]*[[:digit:]]\+' ${OUTPUT_DIR}/$*.cov |wc -l` of `sloccount $*.c |grep "Total Physical" | sed s/^[[:alpha:],[:space:],\(,\),\=]*//`

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

# This target is used for collecting data from the experiment's result into experiment.csv file.
experiment: core-experiment
	( cd ../utils ; CC=${CC} make treecmp ) 
	rm -f ${EXPERIMENT_CSV}
	echo "Directory,Time, #instructions,#error,#completed paths,#error paths,#subsumed paths,#program exit paths,Average branching depth of completed paths,Average branching depth of subsumption paths,Average instructions of completed paths, Average instructions of subsumed paths,Icov,Bcov,llvm-cov Line coverage,SLOC,Time for actual solver calls in subsumption check (ms),Number of solver calls for subsumption check,Number of solver calls for subsumption check that resulted in subsumption failure,Average table entries per subsumption checkpoint,Average solver calls per subsumption check,Number of subsumption checks,KLEE paths saved,Tracer-X new paths,KLEE paths before last Tracer-X path" >> ${EXPERIMENT_CSV}; \
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
				grep '^[[:space:]]*[[:digit:]]\+' $$program$$ext/$$program.cov |wc -l |tr -d '\n' >> ${EXPERIMENT_CSV}; \
				printf ", " >> ${EXPERIMENT_CSV}; \
				if [ -e $$program$$ext/SLocCountLog.txt ]; then \
					grep "Total Physical Source Lines of Code (SLOC)" ${CURDIR}/$$program$$ext/SLocCountLog.txt | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' | tr -d ',' >> ${EXPERIMENT_CSV}; \
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

# This target is used for running experiment with LLBMC.
%.llbmc :
	if [ ! -d ${LLBMC_OUTPUT_DIR} ]; then \
		mkdir ${LLBMC_OUTPUT_DIR}; \
	fi ; \
	${CC} -emit-llvm -c ${CFLAGS} $*.c -o $*.bc ; \
	llbmc ${LLBMC_OPTIONS} $*.bc > ${LLBMC_OUTPUT_DIR}/$* ; \
	rm -rf $*.bc ; \

# This target is used for collecting data from LLBMC experiment into CSV file.
experiment-llbmc:
	rm -f ${LLBMC_EXPERIMENT_CSV} ; \
	echo "Program, Time for performing transformations on LLVM IR,Time for performing logical encoding,Time for performing formula transformations,Time for running SMT solver (STP with MiniSat), Total time,Error status" >> ${LLBMC_EXPERIMENT_CSV} ; \
	for program in ${EXPERIMENT_SET} ; \
	do \
		if [ -e ${LLBMC_OUTPUT_DIR}/$$program ]; then \
			printf "$$program," >> ${LLBMC_EXPERIMENT_CSV} ; \
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
	done ; \

