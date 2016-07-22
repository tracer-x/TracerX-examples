# Makefile to build and run the examples using KLEE.
#
# Copyright 2015, 2016 National University of Singapore

# We enable execution tree (tree.dot) output as the examples
# in this directory are small.
EXTRA_OPTIONS=-output-tree -interpolation-stat -write-pcs -use-query-log=all:pc,all:smt2 -clpr-log

JOIN_TARGETS=test-use-clpr test-join test-count test-sum

default: ${JOIN_TARGETS}

include ../Makefile.common

clean: standard-clean
	rm -rf ${JOIN_TARGETS}

# For testing -use-clpr option in loading multiple CLP(R) files
test-use-clpr: join1.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=dummy1.clpr -use-clpr=dummy2.clpr -output-dir=$@ $<
	mv -f /tmp/clpr-* $@/clpr.log

# For testing actual klee_join mechanism
test-join: join2.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=dummy1.clpr -output-dir=$@ $<
	mv -f /tmp/clpr-* $@/clpr.log

# For testing the count example
test-count: count.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=count.clpr -output-dir=$@ $<
	mv -f /tmp/clpr-* $@/clpr.log

# For testing the sum example
test-sum: sum.bc
	LD_LIBRARY_PATH=${EXTRA_LD_LIBRARY_PATH} time ${KLEE} ${KLEE_FLAGS} -use-clpr=sum.clpr -output-dir=$@ $<
	mv -f /tmp/clpr-* $@/clpr.log


