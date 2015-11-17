Simple examples for running with KLEE.

Copyright 2015 National University of Singapore

This Makefile will create klee output directories
<example-name>.klee which also contains the .dot files,
and also <example-name>.inputs that shows the input
values for each test. 

Sample usages:

To run all examples from the default targets:

make

To run a single example, e.g., number.c from the Hansen,
Schachte, and Sondergaard's article. These are currenly
separated from the default targets as they test the
performance limits of KLEE. The method also works for
anything in the defaul targets.

make number.klee

To build an LLVM IR file of number.c:

make number.s

To clean the directory:

make clean

