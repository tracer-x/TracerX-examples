Simple examples for running with KLEE.

Copyright 2015 National University of Singapore

To run the examples using KLEE, first edit Makefile.common to set the
right variable values for your system.

Each directory contains a suite of simple examples.

  basic  - Basic examples

  hansen - Examples from Hansen, Schachte, Sondergaard's paper "State
           Joining and Splitting for the Symbolic Execution of
           Binaries." These tests the performance limits of KLEE.

  llbmc  - Examples from LLBMC 2013.1 distribution. The license
           information is included in the license/LLBMC_LICENSE file.

To run the the example(s) in a particular directory, say basic, change
your current directory to the basic directory.

The Makefile in each directory will create klee output directories
<example-name>.klee which also contains the .dot files, and also
<example-name>.inputs that shows the input values for each test.

Sample usages:

To run all examples with KLEE:

make

To run a single example, e.g., addition.c in the basic directory:

make addition.klee

To build an LLVM IR file of number.c:

make addition.s

To clean the directory:

make clean

