# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore

EXTRA_OPTIONS=-interpolation-stat

# We remove bubble_llbmc.klee from KLEE targets, as it
# is to be run with LLBMC
TARGETS=$(subst bubble_llbmc.klee,,$(patsubst %.c,%.klee,$(wildcard *.c)))

KLEE_TARGETS1=Regexp.klee1 RegexpSize10.klee1 RegexpSize15.klee1 RegexpSize8.klee1 RegexpSize9.klee1 bubble12.klee1 bubble12_unsafe.klee1 bubble9.klee1 bubble9_unsafe.klee1
KLEE_TARGETS2=Regexp.klee2 RegexpSize10.klee2 RegexpSize15.klee2 RegexpSize8.klee2 RegexpSize9.klee2 bubble12.klee2 bubble12_unsafe.klee2 bubble9.klee2 bubble9_unsafe.klee2
TRACERX_TARGETS1=Regexp.tracerx1 RegexpSize10.tracerx1 RegexpSize15.tracerx1 RegexpSize8.tracerx1 RegexpSize9.tracerx1 bubble12.tracerx1 bubble12_unsafe.tracerx1 bubble9.tracerx1 bubble9_unsafe.tracerx1
TRACERX_TARGETS2=Regexp.tracerx2 RegexpSize10.tracerx2 RegexpSize15.tracerx2 RegexpSize8.tracerx2 RegexpSize9.tracerx2 bubble12.tracerx2 bubble12_unsafe.tracerx2 bubble9.tracerx2 bubble9_unsafe.tracerx2
TRACERX_TARGETS3=Regexp.tracerx3 RegexpSize10.tracerx3 RegexpSize15.tracerx3 RegexpSize8.tracerx3 RegexpSize9.tracerx3 bubble12.tracerx3 bubble12_unsafe.tracerx3 bubble9.tracerx3 bubble9_unsafe.tracerx3
TRACERX_TARGETS4=Regexp.tracerx4 RegexpSize10.tracerx4 RegexpSize15.tracerx4 RegexpSize8.tracerx4 RegexpSize9.tracerx4 bubble12.tracerx4 bubble12_unsafe.tracerx4 bubble9.tracerx4 bubble9_unsafe.tracerx4

LLBMC=${HOME}/software/llbmc-2013.1-Linux_64
LLBMC_OUTPUT_DIR=${CURDIR}/LLBMC_OUTPUT
LLBMC_OPTIONS=--ignore-missing-function-bodies -function-name=main -max-loop-iterations=5 -max-function-call-depth=10

ECHO_TARGETS=echo.echo0 echo_nosyscall.echo0 echo_small.echo0
TR_TARGETS=tr.tr0 tr_nosyscall.tr0 tr_small.tr0
BUBBLE_TARGETS=bubble9.bubble0 bubble12.bubble0 bubble9_unsafe.bubble0 bubble12_unsafe.bubble0

EXTRA_REMOVAL=${TR_TARGETS} ${ECHO_TARGETS} ${BUBBLE_TARGETS}

include ../Makefile.common

#################################################################################
# Below are special targets for special run configurations                      #
#                                                                               #
# To run all programs under specific group targets, please run:                 #
#   Make <group_target>                                                         #
#     Example:                                                                  #
#       Make echo  ==> run echo, echo_nosyscall and echo_small                  #
#       Make tr  ==> run tr, tr_nosyscall, and tr_small                         #
#       Make bubble  ==> run bubble9, bubble12, bubble9_unsafe, bubble12_unsafe #
# To run only a specific program, please run:                                   #
#   Make <program_name>.<suffixes_group>                                        #
#     Example:                                                                  #
#       Make echo_nosyscall.echo0 (only run echo_nosyscall)                     #
#       Make tr_nosyscall.tr0 (only run tr_nosyscall)                           #
#       Make bubble9.bubble0 (only run bubble9)                                 #
#################################################################################

bubble_llbmc: bubble_llbmc.c
	${CC} -c -g -emit-llvm -I${LLBMC}/examples bubble_llbmc.c -o bubble_llbmc.o
	llbmc -max-loop-iterations=10 bubble_llbmc.o

echo: ${ECHO_TARGETS}
	rm -rf klee-*
	rm -f $^

# For running Minix tr versions
tr: ${TR_TARGETS}
	rm -rf klee-*
	rm -f $^

bubble: ${BUBBLE_TARGETS}
	rm -rf klee-*
	rm -f $^


clean: standard-clean
	rm -rf ${KLEE_TARGETS1} ${KLEE_TARGETS2} ${TRACERX_TARGETS1} ${TRACERX_TARGETS2} ${TRACERX_TARGETS3} ${TRACERX_TARGETS4}

.SUFFIXES: .tr0 .echo0 .bubble0

.bc.echo0:
	rm -rf $@ klee-*
	time ${KLEE} -solver-backend=z3 -max-time=600 -interpolation-stat --only-output-states-covering-new --libc=uclibc --posix-runtime --allow-external-sym-calls $< --sym-args 0 2 4
	touch $@

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
	KLEE_OPTIONS="-solver-backend=stp -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.klee2 : 
	KLEE_OPTIONS="-no-interpolation -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.tracerx1 : 
	KLEE_OPTIONS="--search=dfs -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.tracerx2 : 
	KLEE_OPTIONS="--search=dfs -max-subsumption-failure=3 -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.tracerx3 : 
	KLEE_OPTIONS="-solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.tracerx4 : 
	KLEE_OPTIONS="-max-subsumption-failure=3 -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

# This target is used for running experiments. The conducted experiments involved different option settings of KLEE and Tracer-X which
# can be seen in %.klee1, %.klee2, %.tracerx1, %.tracerx2, %.tracerx3, and %.tracerx4 target.
%.klee-exp-201609: 
	${CC} -emit-llvm ${CFLAGS} -c $*.c
	if [ $* = "Regexp" ] || [ $* = "RegexpSize10" ] || [ $* = "RegexpSize15" ] || [ $* = "RegexpSize8" ] || [ $* = "RegexpSize9" ] ; then \
		KLEE_MORE_OPTIONS="--only-output-states-covering-new" ; \
	fi ; \
	rm -rf $@; \
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} -interpolation-stat ${KLEE_OPTIONS} $$KLEE_MORE_OPTIONS -output-dir=${OUTPUT_DIR} ${CURDIR}/$*.bc ; \
	rm -f $*.bc; \
	if [ -e ${OUTPUT_DIR}/tree.dot ]; then \
		dot -Tsvg ${OUTPUT_DIR}/tree.dot -o ${OUTPUT_DIR}/$*.svg ; \
	fi
	sloccount $*.c > ${OUTPUT_DIR}/SLocCountLog.txt 2>&1

exp-201609:
	for program in Regexp RegexpSize10 RegexpSize15 RegexpSize8 RegexpSize9 bubble12 bubble12_unsafe bubble9 bubble9_unsafe; \
	do \
		make $$program.klee1;    \
		make $$program.klee2;    \
		make $$program.tracerx1; \
		make $$program.tracerx2; \
		make $$program.tracerx3; \
		make $$program.tracerx4; \
	done

# This target is used for collecting data from experiment exp-201609 result into log-exp-201609.csv file.
csv-exp-201609:
	rm -f log-exp-201609.csv
	echo "Directory,Time, #instructions,#completed paths,#error paths,#subsumed paths,#program exit paths,Average branching depth of completed paths,Average branching depth of subsumption paths,Average instructions of completed paths, Average instructions of subsumed paths,Icov,Bcov,SLOC,Time for actual solver calls in subsumption check (ms),Number of solver calls for subsumption check,Number of solver calls for subsumption check that resulted in subsumption failure,Average table entries per subsumption checkpoint,Average solver calls per subsumption check,Number of subsumption checks,Untraversed path count" >> log-exp-201609.csv; \
	for ext in .klee1 .klee2 .tracerx1 .tracerx2 .tracerx3 .tracerx4; \
	do \
		for program in Regexp RegexpSize10 RegexpSize15 RegexpSize8 RegexpSize9 bubble12 bubble12_unsafe bubble9 bubble9_unsafe; \
		do \
			if [ -d $$program$$ext ]; then \
				printf "$$program$$ext," >> log-exp-201609.csv; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f4  | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "KLEE: done: total instructions" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/'| tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "KLEE: done: completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d ', among which\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "KLEE: done:     error paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "KLEE: done:     subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "KLEE: done:     program exit paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "average branching depth of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "average branching depth of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "average instructions of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "average instructions of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f5 | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f6 | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				if [ -e $$program$$ext/SLocCountLog.txt ]; then \
					grep "Total Physical Source Lines of Code (SLOC)" ${CURDIR}/$$program$$ext/SLocCountLog.txt | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' | tr -d ',' >> log-exp-201609.csv; \
				fi ; \
				printf ", " >> log-exp-201609.csv; \
				grep "Time for actual solver calls in subsumption check (ms)" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\1/'| tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\2/' | tr -d ')\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "Average table entries per subsumption checkpoint" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "Average solver calls per subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
				grep "KLEE: done:     Number of subsumption checks" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> log-exp-201609.csv; \
				printf ", " >> log-exp-201609.csv; \
			fi ; \
			if [ $$ext == .tracerx1 -o $$ext == .tracerx2 -o $$ext == .tracerx3 -o $$ext == .tracerx4 ] ;  then \
				UNTRAVERSEDKLEEPATH_COUNT=0 ; \
				for PATHFILE in $$program$$ext/*.path ; \
				do \
					LENTRACERPATH=`cat $$PATHFILE | wc -l` ; \
					for KLEEPATHFILE in $$program.klee1/*.path ; \
					do \
						LENKLEEPATH=`cat $$KLEEPATHFILE | wc -l` ; \
						if [ "$$LENTRACERPATH" -lt "$$LENKLEEPATH" ] ; \
						then \
							rm -f $$KLEEPATHFILE.short ; \
							head --lines=$$LENTRACERPATH $$KLEEPATHFILE > $$KLEEPATHFILE.short ; \
							diff $$PATHFILE $$KLEEPATHFILE.short > /dev/null ; \
							if [ "$$?" -eq "0" ] ; \
							then \
								UNTRAVERSEDKLEEPATH_COUNT=$$((UNTRAVERSEDKLEEPATH_COUNT+1)) ; \
							fi ; \
						fi ; \
					done ; \
				done ; \
				printf $$UNTRAVERSEDKLEEPATH_COUNT >> log-exp-201609.csv; \
			fi ; \
			printf "\n" >> log-exp-201609.csv; \
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

# This target is used for collecting data from LLBMC experiment into log-llbmc file.
csv-exp-201609-llbmc:
	rm -f ${LLBMC_OUTPUT_DIR}/log-llbmc.csv ; \
	echo "Program, Time for performing transformations on LLVM IR,Time for performing logical encoding,Time for performing formula transformations,Time for running SMT solver (STP with MiniSat), Total time,Error status" >> ${LLBMC_OUTPUT_DIR}/log-llbmc.csv; \
	for program in Regexp RegexpSize10 RegexpSize15 RegexpSize8 RegexpSize9 bubble12 bubble12_unsafe bubble9 bubble9_unsafe ; \
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

