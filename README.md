Simple examples for running with KLEE

Copyright 2015, 2016 National University of Singapore

To run the examples using KLEE, first edit Makefile.common to set the
right variable values for your system.

Each directory contains a suite of simple examples.

- **basic**  - Basic examples.

- **hansen** - Examples from Hansen, Schachte, Sondergaard's paper *State Joining and Splitting for the Symbolic Execution of Binaries.* These test various aspects of symbolic execution.

- **llbmc** - Examples from LLBMC 2013.1 distribution. The examples were modified on 17 November 2015 for running with KLEE, e.g., adding main method and replaced LLBMC API calls with the corresponding KLEE API calls. The LLBMC license information is included in the `license/LLBMC_LICENSE` file.

- **scalability** - Examples that tests scalability, including `Regexp.c`, an example from KLEE tutorial at http://klee.github.io/tutorials

- **llbmc-bench** - Examples of C/C++ programs, with the fix suggested by Jonas Wagner. There are several modifications from the original version at http://llbmc.org/files/downloads/llbmc-bench-1.1.tgz for running with KLEE, e.g., replaced LLBMC API calls with the corresponding KLEE API calls.

- **coreutils** - Examples of 89 stand-alone programs in the GNU Coreutils-6.10 utility suite. In this version, KLEE able to find some bugs and reported them in https://www.doc.ic.ac.uk/~cristic/papers/klee-osdi-08.pdf.

To run the examples, first edit `Makefile.common` to set the right values for your environment. Then to run the the example(s) in a particular directory, say `basic`, change your current directory to the `basic` directory.

The Makefile in each directory will create KLEE output directories `<example-name>.klee` which also contains the `.dot` files, and also `<example-name>.inputs` files that show the input values for each test.

Sample usages:
- To run all examples with KLEE:

  `make`

- To run a single example, e.g., addition.c in the basic directory using Z3 solver and interpolation:

  `make addition.klee`

- For additional coverage statistics, instead run:

  `make addition.cov`

- To run a single example, e.g., addition.c in the basic directory using STP solver and without interpolation:

  `make addition.stpklee`

- And for additionally generating coverage statistics using STP solver backend and without interpolation, run instead:

  `make addition.stpcov`

- To build an LLVM IR file of `addition.c`:

  `make addition.s`

- To clean the directory:

  `make clean`

