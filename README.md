Simple examples for running with KLEE
-------------------------------------

Copyright 2015, 2016 National University of Singapore

To run the examples using KLEE, first edit Makefile.common to set the
right variable values for your system.

Each directory contains a suite of simple examples.

- **basic**  - Basic examples.

- **abstract** - Examples for testing `klee_abstract` API.

- **hansen** - Examples from Hansen, Schachte, Sondergaard's paper *State Joining and Splitting for the Symbolic Execution of Binaries.* These test various aspects of symbolic execution.

- **llbmc** - Examples from LLBMC 2013.1 distribution. The examples were modified on 17 November 2015 for running with KLEE, e.g., adding main method and replaced LLBMC API calls with the corresponding KLEE API calls. The LLBMC license information is included in the `license/LLBMC_LICENSE` file.

- **scalability** - Examples that tests scalability, including `Regexp.c`, an example from KLEE tutorial at http://klee.github.io/tutorials

- **llbmc-bench** - Examples of C/C++ programs, with the fix suggested by Jonas Wagner. There are several modifications from the original version at http://llbmc.org/files/downloads/llbmc-bench-1.1.tgz for running with KLEE, e.g., replaced LLBMC API calls with the corresponding KLEE API calls.

- **join** - Examples for testing `klee_join` API.

- **coreutils** - Examples of 89 stand-alone programs in the GNU Coreutils-6.10 utility suite. In this version, KLEE was able to find some bugs and they are reported in the [OSDI Paper](https://www.doc.ic.ac.uk/~cristic/papers/klee-osdi-08.pdf). The `coreutils` directory contains `coreutils-6.10` subdirectory of GNU Coreutils 6.10.

Running examples other than *join* and *coreutils*
--------------------------------------------------

Instruction on running the examples in the `join` and `coreutils` directories can be found later in this document. To run other examples, first edit `Makefile.common` to set the right values for your environment. Then to run the the example(s) in a particular directory, say `basic`, change your current directory to the `basic` directory.

The Makefile in each directory will create KLEE output directories `<example-name>.klee` which also contains the `.dot` files, and also `<example-name>.inputs` files that show the input values for each test.

Sample usages:
- To run a single example, e.g., addition.c in the basic directory with KLEE using Z3 solver and interpolation:

  `make addition.klee`

  If the file `subsumption.dat` exists, this may also perform a regression test on the number of subsumptions compared to reference data in `subsumption.dat`.

- For running addition.c with KLEE using Z3 solver and interpolation, and with additional coverage statistics, instead run:

  `make addition.cov`

- To run all examples with KLEE using Z3 solver and interpolation:

  `make`

  This is the same as executing `make <example_name>.klee` for all examples.

- To run a single example, e.g., addition.c in the basic directory using STP solver and without interpolation:

  `make addition.stpklee`

- And for additionally generating coverage statistics using STP solver backend and without interpolation, run instead:

  `make addition.stpcov`

- To build an LLVM IR file of `addition.c`:

  `make addition.s`

- To clean the directory:

  `make clean`

Running *join* examples
-----------------------

The examples in the `join` subdirectory requires Tracer-X KLEE to be compiled with CLP(R) 1.2l support. The `Makefile` tests can be run in the following way:

- For running Tracer-X KLEE with `join1.c` to test the ability of `-use-clpr` option to load multiple CLP(R) files.

  `make test-use-clpr`

- For running Tracer-X KLEE with `join2.c` to actually test the subsumption ability of Tracer-X KLEE with `klee_join`.

  `make test-join`

- Make `test-count` and `test-sum` targets are for running Tracer-X KLEE with larger examples to test the subsumption ability using `klee_join`. Run, e.g.:

  `make test-count`

Running *coreutils* examples
----------------------------

- *Prerequisites:* 
   1. `whole-program-llvm`. This can be done by cloning it from GitHub, i.e.:
     
      `git clone https://github.com/travitch/whole-program-llvm.git`

   2. You may/may not need an older version of GNU texinfo. The build does not work with texinfo 5.2, but known to work with 4.13. Texinfo 4.13 can be found [here](http://ftp.gnu.org/gnu/texinfo/texinfo-4.13.tar.gz). You may install Texinfo 4.13 with installation prefix `<texinfo_prefix>`, and set `EXTRA_PATH` in `Makefile.common` to include `<texinfo_prefix>/bin`.

- For testing a Coreutils 6.10 program with KLEE, first please edit the top-level `Makefile.common` to set suitable values for various variables, then:
   1. `cd coreutils`
   2. Run `make` in any of these ways:
       - `make build` - To build Coreutils 6.10 twice: one with LLVM (in `coreutils/coreutils-6.10/obj-llvm/src`) and another with GCOV (in `coreutils/coreutils-6.10/obj-gcov/src`) without running KLEE.
       - Just `make` - Runs the test-case generation on all programs: it will build Coreutils 6.10 if this is not done already.
       - `make <program_name>.klee` - Runs the test-case generation on `<program_name>`: it will build Coreutils 6.10 if this is not done already. Here, `<program_name>` is one of the Coreutils programs whose executable file is found as `coreutils/coreutils-6.10/obj-llvm/src/<program_name>`. The output will be the result of Tracer-X KLEE run on the program and its coverage information.
       - `make <program_name>.stpklee` - Runs the test-case generation on `<program_name>` similar to `make <program_name>.klee`, however, Tracer-X KLEE will be invoked with `--select-solver=stp` which disables interpolation and uses STP, resulting in standard KLEE run using STP.

- Note that using `make`, the test cases generated by Tracer-X KLEE will be in `coreutils/<program_name>.klee` and the test cases generated by KLEE/STP will be in `coreutils/<program_name>.stpklee`.
