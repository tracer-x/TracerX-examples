#!/bin/bash
cd coreutils
make clean
coreutils_program='cut expand fmt fold join pr printf sort sum tail tsort uniq wc factor seq' 

for program in $coreutils_program
do
	make $program.klee1
	make $program.klee2
	make $program.tracerx1
	make $program.tracerx2
	make $program.tracerx3
	make $program.tracerx4
done

