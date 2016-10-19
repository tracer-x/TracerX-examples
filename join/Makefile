# Makefile to build and run the examples using KLEE.
#
# Copyright 2015, 2016 National University of Singapore

# We enable execution tree (tree.dot) output as the examples
# in this directory are small.
EXTRA_OPTIONS=-output-tree -interpolation-stat -write-pcs -use-query-log=all:pc,all:smt2 -clpr-log

# This is for the options passed onto the tested program, e.g.,
# --sym-arg
PROGRAM_OPTIONS=

JOIN_TARGETS=test-use-clpr test-join test-nosub1 test-nosub2 test-sub test-count test-sum

default: ${JOIN_TARGETS}

include ../Makefile.common

clean: standard-clean
	rm -rf ${JOIN_TARGETS}

# For testing -use-clpr option in loading multiple CLP(R) files
test-use-clpr: join1.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=dummy1.clpr -use-clpr=dummy2.clpr -output-dir=$@ $<
	mv -f /tmp/clpr-* $@/clpr.log
	# Create SVGs from *.dot files
	for DOTFILE in $@/*.dot ; do \
		SVGFILE=`echo -n $$DOTFILE | sed -e s/\.dot/\.svg/ -` ; \
		dot -Tsvg $$DOTFILE -o $$SVGFILE ; \
	done

# For testing actual klee_join mechanism
test-join: join2.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=dummy1.clpr -output-dir=$@ $<
	mv -f /tmp/clpr-* $@/clpr.log
	# Create SVGs from *.dot files
	for DOTFILE in $@/*.dot ; do \
		SVGFILE=`echo -n $$DOTFILE | sed -e s/\.dot/\.svg/ -` ; \
		dot -Tsvg $$DOTFILE -o $$SVGFILE ; \
	done

# Simple test for no subsumption I
test-nosub1: join3.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=dummy1.clpr -output-dir=$@ $< 2> $@.log
	mv -f /tmp/clpr-* $@/clpr.log
	mv -f $@.log $@/klee.log
	# Create SVGs from *.dot files
	for DOTFILE in $@/*.dot ; do \
		SVGFILE=`echo -n $$DOTFILE | sed -e s/\.dot/\.svg/ -` ; \
		dot -Tsvg $$DOTFILE -o $$SVGFILE ; \
	done
	grep "subsumed paths = 0" $@/klee.log

# Simple test for no subsumption II
test-nosub2: join4.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=dummy1.clpr -output-dir=$@ $< 2> $@.log
	mv -f /tmp/clpr-* $@/clpr.log
	mv -f $@.log $@/klee.log
	# Create SVGs from *.dot files
	for DOTFILE in $@/*.dot ; do \
		SVGFILE=`echo -n $$DOTFILE | sed -e s/\.dot/\.svg/ -` ; \
		dot -Tsvg $$DOTFILE -o $$SVGFILE ; \
	done
	grep "subsumed paths = 0" $@/klee.log

# Simple test for subsumption
test-sub: join5.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=dummy1.clpr -output-dir=$@ $< 2> $@.log
	mv -f /tmp/clpr-* $@/clpr.log
	mv -f $@.log $@/klee.log
	# Create SVGs from *.dot files
	for DOTFILE in $@/*.dot ; do \
		SVGFILE=`echo -n $$DOTFILE | sed -e s/\.dot/\.svg/ -` ; \
		dot -Tsvg $$DOTFILE -o $$SVGFILE ; \
	done
	grep "subsumed paths = 1" $@/klee.log

# For testing the count example
test-count: count.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=count.clpr -output-dir=$@ $<
	mv -f /tmp/clpr-* $@/clpr.log
	# Create SVGs from *.dot files
	for DOTFILE in $@/*.dot ; do \
		SVGFILE=`echo -n $$DOTFILE | sed -e s/\.dot/\.svg/ -` ; \
		dot -Tsvg $$DOTFILE -o $$SVGFILE ; \
	done

# For testing the sum example
test-sum: sum.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=sum.clpr -output-dir=$@ $<
	mv -f /tmp/clpr-* $@/clpr.log
	# Create SVGs from *.dot files
	for DOTFILE in $@/*.dot ; do \
		SVGFILE=`echo -n $$DOTFILE | sed -e s/\.dot/\.svg/ -` ; \
		dot -Tsvg $$DOTFILE -o $$SVGFILE ; \
	done


