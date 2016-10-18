# Makefile to build and run the examples using KLEE.
#
# Copyright 2016 National University of Singapore
#
# Symbolic arguments for testing coreutils is following
# http://klee.github.io/docs/coreutils-experiments/

COREUTILS_DIR=${CURDIR}/coreutils-6.10
COREUTILS_LLVM_DIR=${COREUTILS_DIR}/obj-llvm
COREUTILS_GCOV_DIR=${COREUTILS_DIR}/obj-gcov
COREUTILS_SRC=${COREUTILS_DIR}/src
CFLAGS_LLBMC_COREUTILS=-g -I${COREUTILS_LLVM_DIR}/lib -I${COREUTILS_SRC} -I/${COREUTILS_DIR}/lib
LLBMC_OUTPUT_DIR=${CURDIR}/LLBMC_OUTPUT
LLBMC_OPTIONS=--ignore-missing-function-bodies -function-name=main -max-loop-iterations=5 -max-function-call-depth=10

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

KLEE_COREUTILS_BASIC_OPTIONS=--simplify-sym-indices --write-cvcs --write-cov --output-module \
	--max-memory=1000 --disable-inlining --optimize --use-forked-solver \
	--use-cex-cache --libc=uclibc --posix-runtime \
	--allow-external-sym-calls --only-output-states-covering-new \
	--max-sym-array-size=4096 --max-instruction-time=30. \
	--watchdog --max-memory-inhibit=false --max-static-fork-pct=1 \
	--max-static-solve-pct=1 --max-static-cpfork-pct=1 --switch-type=internal \
	--randomize-fork \
	--use-batching-search --batch-instructions=10000

# Comment this out if the above options are preferred
#KLEE_COREUTILS_OPTIONS=--libc=uclibc --posix-runtime --optimize --output-tree --max-time=60.

# From http://klee.github.io/docs/coreutils-experiments/
TARGETS=[ arch base64 basename cat chcon chgrp chmod chown chroot cksum comm cp csplit cut date dd df dircolors dirname du echo env expand expr factor false fmt fold head hostid hostname id ginstall join kill link ln logname ls md5sum mkdir mkfifo mknod mktemp mv nice nl nohup od paste pathchk pinky pr printenv printf ptx pwd readlink rm rmdir runcon seq setuidgid shred shuf sleep sort split stat stty sum sync tac tail tee touch tr tsort tty uname unexpand uniq unlink uptime users wc whoami who yes 

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

# Coreutils benchmark set for September 2016 experiment
EXP201609_SET=cut expand join sum tsort uniq wc factor seq comm dirname head pathchk split

EXP201609_CSV=exp-201609.csv

KLEE_TARGETS1=$(EXP201609_SET:=.klee1)
KLEE_TARGETS2=$(EXP201609_SET:=.klee2)
TRACERX_TARGETS1=$(EXP201609_SET:=.tracerx1)
TRACERX_TARGETS2=$(EXP201609_SET:=.tracerx2)
TRACERX_TARGETS3=$(EXP201609_SET:=.tracerx3)
TRACERX_TARGETS4=$(EXP201609_SET:=.tracerx4)

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
		../configure --disable-nls CFLAGS="-g -fprofile-arcs -ftest-coverage" --enable-install-program=arch,hostname ; \
		make; \
		make -C src arch hostname \
	)

# In the following target:
# * We build arch and hostname after make is executed, as it appears that
#   make does not build them.
# * We skip whole-program bitcode creation for groups as it is a script.
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
		../configure --disable-nls CFLAGS="-g" --enable-install-program=arch,hostname ; \
		make ; \
		rm -f src/*.gcov \
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

%.klee1 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -solver-backend=z3 -no-interpolation -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.klee2 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -solver-backend=z3 -no-interpolation -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.tracerx1 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.tracerx2 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=dfs -max-subsumption-failure=3 -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.tracerx3 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

%.tracerx4 : 
	KLEE_COREUTILS_MORE_OPTIONS="--search=random-path --search=nurs:covnew -max-subsumption-failure=3 -solver-backend=z3 -max-time=7200 -write-paths" OUTPUT_DIR=${CURDIR}/$@ make $*.klee-exp-201609

# This target is used for running experiments. The conducted experiments involved different option settings of KLEE and Tracer-X which
# can be seen in %.klee1, %.klee2, %.tracerx1, %.tracerx2, %.tracerx3, and %.tracerx4 target.
%.klee-exp-201609: build
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
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} -interpolation-stat ${KLEE_COREUTILS_BASIC_OPTIONS} ${KLEE_COREUTILS_MORE_OPTIONS} --environ=${CURDIR}/test.env --run-in=${CURDIR}/sandbox -output-dir=${OUTPUT_DIR} ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_ARGS -max-fail 1 ; \
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
	if [ $* = "arch" ]; then \
		GCOV_OBJECTS="uname uname-arch" ; \
	elif [ $* = "[" ]; then \
		GCOV_OBJECTS="lbracket" ; \
	elif [ $* = "cp" ]; then \
		GCOV_OBJECTS="cp copy cp-hash" ; \
	elif [ $* = "dir" ]; then \
		GCOV_OBJECTS="ls ls-dir" ; \
	elif [ $* = "vdir" ]; then \
		GCOV_OBJECTS="ls ls-vdir" ; \
	elif [ $* = "ls" ]; then \
		GCOV_OBJECTS="ls ls-ls" ; \
	elif [ $* = "chown" ]; then \
		GCOV_OBJECTS="chown chown-core" ; \
	elif [ $* = "chgrp" ]; then \
		GCOV_OBJECTS="chgrp chown-core" ; \
	elif [ $* = "mv" ]; then \
		GCOV_OBJECTS="mv remove copy cp-hash" ; \
	elif [ $* = "rm" ]; then \
		GCOV_OBJECTS="rm remove" ; \
	elif [ $* = "uname" ]; then \
		GCOV_OBJECTS="uname uname-uname" ; \
	elif [ $* = "sha1sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha224sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha256sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha384sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha512sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	else \
		GCOV_OBJECTS=$* ; \
	fi ; \
	rm -f ${COREUTILS_GCOV_DIR}/src/*.gcda; \
	( cd ${COREUTILS_GCOV_DIR}/src ; \
		${KLEE_REPLAY} $* ${OUTPUT_DIR}/*.ktest ; \
		for GCOV_OBJ in $$GCOV_OBJECTS ; do \
			gcov -o $$GCOV_OBJ $* ; \
		done \
	) > ${OUTPUT_DIR}/GcovLog.txt 2>&1
	rm -f ${COREUTILS_GCOV_DIR}/src/*.gcda; 
	@echo =================================================================
	@echo Measure number of lines of code by using SLOCCount...
	@echo =================================================================
	sloccount ${COREUTILS_SRC}/$*.c > ${OUTPUT_DIR}/SLocCountLog.txt 2>&1

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
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} -interpolation-stat ${KLEE_COREUTILS_OPTIONS} -solver-backend=z3 --environ=${CURDIR}/test.env --run-in=${CURDIR}/sandbox -output-dir=${CURDIR}/$@ ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_ARGS -max-fail 1 ; \
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Create SVGs from tree.dot file if any ...
	@echo =================================================================
	if [ -e ${CURDIR}/$@/tree.dot ]; then \
		dot -Tsvg ${CURDIR}/$@/tree.dot -o ${CURDIR}/$@/$*.svg ; \
	fi
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	if [ $* = "arch" ]; then \
		GCOV_OBJECTS="uname uname-arch" ; \
	elif [ $* = "[" ]; then \
		GCOV_OBJECTS="lbracket" ; \
	elif [ $* = "cp" ]; then \
		GCOV_OBJECTS="cp copy cp-hash" ; \
	elif [ $* = "dir" ]; then \
		GCOV_OBJECTS="ls ls-dir" ; \
	elif [ $* = "vdir" ]; then \
		GCOV_OBJECTS="ls ls-vdir" ; \
	elif [ $* = "ls" ]; then \
		GCOV_OBJECTS="ls ls-ls" ; \
	elif [ $* = "chown" ]; then \
		GCOV_OBJECTS="chown chown-core" ; \
	elif [ $* = "chgrp" ]; then \
		GCOV_OBJECTS="chgrp chown-core" ; \
	elif [ $* = "mv" ]; then \
		GCOV_OBJECTS="mv remove copy cp-hash" ; \
	elif [ $* = "rm" ]; then \
		GCOV_OBJECTS="rm remove" ; \
	elif [ $* = "uname" ]; then \
		GCOV_OBJECTS="uname uname-uname" ; \
	elif [ $* = "sha1sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha224sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha256sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha384sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha512sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	else \
		GCOV_OBJECTS=$* ; \
	fi ; \
	rm -f ${COREUTILS_GCOV_DIR}/src/*.gcda; \
	( cd ${COREUTILS_GCOV_DIR}/src ; \
		${KLEE_REPLAY} $* ${CURDIR}/$@/*.ktest ; \
		for GCOV_OBJ in $$GCOV_OBJECTS ; do \
			gcov -o $$GCOV_OBJ $* ; \
		done \
	) > ${CURDIR}/$@/GcovLog.txt 2>&1
	rm -f ${COREUTILS_GCOV_DIR}/src/*.gcda; 

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
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_COREUTILS_OPTIONS} -solver-backend=stp --environ=${CURDIR}/test.env --run-in=sandbox -output-dir=${CURDIR}/$@ ${COREUTILS_LLVM_DIR}/src/$*.bc $$PROGRAM_ARGS -max-fail 1 ;
	# Delete the sandbox
	rm -rf sandbox sandbox.temps
	@echo =================================================================
	@echo Running generated tests to compute coverage ...
	@echo =================================================================
	if [ $* = "arch" ]; then \
		GCOV_OBJECTS="uname uname-arch" ; \
	elif [ $* = "[" ]; then \
		GCOV_OBJECTS="lbracket" ; \
	elif [ $* = "cp" ]; then \
		GCOV_OBJECTS="cp copy cp-hash" ; \
	elif [ $* = "dir" ]; then \
		GCOV_OBJECTS="ls ls-dir" ; \
	elif [ $* = "vdir" ]; then \
		GCOV_OBJECTS="ls ls-vdir" ; \
	elif [ $* = "ls" ]; then \
		GCOV_OBJECTS="ls ls-ls" ; \
	elif [ $* = "chown" ]; then \
		GCOV_OBJECTS="chown chown-core" ; \
	elif [ $* = "chgrp" ]; then \
		GCOV_OBJECTS="chgrp chown-core" ; \
	elif [ $* = "mv" ]; then \
		GCOV_OBJECTS="mv remove copy cp-hash" ; \
	elif [ $* = "rm" ]; then \
		GCOV_OBJECTS="rm remove" ; \
	elif [ $* = "uname" ]; then \
		GCOV_OBJECTS="uname uname-uname" ; \
	elif [ $* = "sha1sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha224sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha256sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha384sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	elif [ $* = "sha512sum" ]; then \
		GCOV_OBJECTS="md5sum" ; \
	else \
		GCOV_OBJECTS=$* ; \
	fi ; \
	rm -f ${COREUTILS_GCOV_DIR}/src/*.gcda; \
	( cd ${COREUTILS_GCOV_DIR}/src ; \
		${KLEE_REPLAY} $* ${CURDIR}/$@/*.ktest ; \
		for GCOV_OBJ in $$GCOV_OBJECTS ; do \
			gcov -o $$GCOV_OBJ $* ; \
		done \
	) > ${CURDIR}/$@/GcovLog.txt 2>&1
	rm -f ${COREUTILS_GCOV_DIR}/src/*.gcda; 

clean:
	rm -rf ${KLEE_TARGETS} ${KLEE_TARGETS1} ${KLEE_TARGETS2} ${KLEE_TARGETS3} ${KLEE_TARGETS4} ${TRACERX_TARGETS1} ${TRACERX_TARGETS2} ${TRACERX_TARGETS3} ${TRACERX_TARGETS4} ${EXP201609_CSV} ${KLEESTP_TARGETS} sandbox sandbox.temps test.env

realclean: clean
	rm -rf ${COREUTILS_GCOV_DIR} ${COREUTILS_LLVM_DIR} 

exp-201609:
	for program in ${EXP201609_SET} ; \
	do \
		make $$program.klee1;    \
		make $$program.klee2;    \
		make $$program.tracerx1; \
		make $$program.tracerx2; \
		make $$program.tracerx3; \
		make $$program.tracerx4; \
	done

# This target is used for collecting data from experiment exp-201609 result into exp-201609.csv file.
csv-exp-201609:
	( cd ../utils ; CC=${CC} make treecmp ) 
	rm -f ${EXP201609_CSV}
	echo "Directory,Time, #instructions,#error,#completed paths,#error paths,#subsumed paths,#program exit paths,Average branching depth of completed paths,Average branching depth of subsumption paths,Average instructions of completed paths, Average instructions of subsumed paths,Icov,Bcov,Gcov,SLOC,Time for actual solver calls in subsumption check (ms),Number of solver calls for subsumption check,Number of solver calls for subsumption check that resulted in subsumption failure,Average table entries per subsumption checkpoint,Average solver calls per subsumption check,Number of subsumption checks,KLEE paths saved,Tracer-X new paths,KLEE paths before last Tracer-X path" >> ${EXP201609_CSV}; \
	for ext in .klee1 .klee2 .tracerx1 .tracerx2 .tracerx3 .tracerx4; \
	do \
		for program in ${EXP201609_SET} ; \
		do \
			if [ -d $$program$$ext ]; then \
				printf "$$program$$ext," >> ${EXP201609_CSV}; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f4  | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "KLEE: done: total instructions" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/'| tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				echo -n `ls $$program$$ext | grep err | wc -l` >> ${EXP201609_CSV} ; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "KLEE: done: completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d ', among which\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "KLEE: done:     error paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "KLEE: done:     subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "KLEE: done:     program exit paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "average branching depth of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "average branching depth of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "average instructions of completed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "average instructions of subsumed paths" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f5 | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				klee-stats $$program$$ext | sed '4q;d' | cut -d '|' -f6 | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				if [ -e $$program$$ext/GcovLog.txt ]; then \
					grep -A1 -P "/$$program.c" ${CURDIR}/$$program$$ext/GcovLog.txt | grep "Lines executed" | sed -E  's/(.*):(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				fi ; \
				printf ", " >> ${EXP201609_CSV}; \
				if [ -e $$program$$ext/SLocCountLog.txt ]; then \
					grep "Total Physical Source Lines of Code (SLOC)" ${CURDIR}/$$program$$ext/SLocCountLog.txt | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' | tr -d ',' >> ${EXP201609_CSV}; \
				fi ; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "Time for actual solver calls in subsumption check (ms)" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\1/'| tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "Number of solver calls for subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | sed -E  's/(.*)\((.*)/\2/' | tr -d ')\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "Average table entries per subsumption checkpoint" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "Average solver calls per subsumption check" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
				grep "KLEE: done:     Number of subsumption checks" ${CURDIR}/$$program$$ext/info | sed -E  's/(.*)=(.*)/\2/' | tr -d '\n' >> ${EXP201609_CSV}; \
				printf ", " >> ${EXP201609_CSV}; \
			fi ; \
			if [ $$ext = .tracerx1 -o $$ext = .tracerx2 ] ;  then \
				( ../utils/treecmp $$program.klee1 $$program$$ext | sed -e 's/\s/\,/g'  ) >> ${EXP201609_CSV} ; \
			else \
				printf "\n" >> ${EXP201609_CSV}; \
			fi ; \
		done ; \
	done

# This target is used for running coreutils experiment with LLBMC. #Arguments in PROGRAM_ARGS have lengths matching that of KLEE runs. For example, Klee runs with --sym-args 0 1 10 --sym-args 0 2 2 which defined in DEFAULT_ARGS, means coreutils programs are triggered with 2 short options (length 2) and 1 long option (length 10). This arguments example in KLEE run is translated into "xx xx xxxxxxxxxx".
%.llbmc :
	if [ $* = "dd" ]; then \
		PROGRAM_ARGS="xxxxxxxxxx xxxxxxxxxx xxxxxxxxxx" ; \
	elif [ $* = "dircolors" ]; then \
		PROGRAM_ARGS="xxxxxxxxxx xxxxxxxxxx xxxxxxxxxx" ; \
	elif [ $* = "echo" ]; then \
		PROGRAM_ARGS="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ; \
	elif [ $* = "expr" ]; then \
		PROGRAM_ARGS="xxx xxx xxxxxxxxxx" ; \
	elif [ $* = "mknod" ]; then \
		PROGRAM_ARGS="xxx xxx xxxxxxxxxx" ; \
	elif [ $* = "od" ]; then \
		PROGRAM_ARGS="xxxxxxxxxx xxxxxxxxxx xxxxxxxxxx" ; \
	elif [ $* = "pathchk" ]; then \
		PROGRAM_ARGS="x x" ; \
	elif [ $* = "printf" ]; then \
		PROGRAM_ARGS="xxxxxxxxxx xxxxxxxxxx xxxxxxxxxx" ; \
	else \
		PROGRAM_ARGS="xx xx xxxxxxxxxx" ; \
	fi ; \
	if [ ! -d ${LLBMC_OUTPUT_DIR} ]; then \
		mkdir ${LLBMC_OUTPUT_DIR}; \
	fi ; \
	${CC} -emit-llvm -c ${CFLAGS_LLBMC_COREUTILS} ${COREUTILS_SRC}/$*.c -o ${COREUTILS_SRC}/$*.bc ; \
	export PATH=${EXTRA_PATH}:$$PATH ; \
	llbmc ${LLBMC_OPTIONS} -arguments="$$PROGRAM_ARGS" ${COREUTILS_SRC}/$*.bc > ${LLBMC_OUTPUT_DIR}/$* ; \
	rm -rf ${COREUTILS_SRC}/$*.bc ; \

# This target is used for collecting data from coreutils LLBMC experiment into log-llbmc file.
csv-exp-201609-llbmc:
	rm -f ${LLBMC_OUTPUT_DIR}/log-llbmc.csv ; \
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
