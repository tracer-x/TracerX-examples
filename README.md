Simple examples for running with Tracer-X KLEE
----------------------------------------------

Copyright 2015, 2016 National University of Singapore

To run the examples using KLEE, first edit Makefile.common to set the
right variable values for your system.

Each directory except **utils** contains a suite of simple examples.

- **basic**  - Basic examples. Some examples are from LLBMC 2013.1 distribution, but modified for running with KLEE. The LLBMC license information is included in the `license/LLBMC_LICENSE` file.

- **abstract** - Examples for testing `klee_abstract` API.

- **scalability** - Examples that tests scalability, including `Regexp.c`, an example from KLEE tutorial at http://klee.github.io/tutorials. Some examples from Hansen, Schachte, Sondergaard's paper *State Joining and Splitting for the Symbolic Execution of Binaries.* These test various aspects of symbolic execution.

- **llbmc-bench** - Examples of C/C++ programs, with the fix suggested by Jonas Wagner. There are several modifications from the original version at http://llbmc.org/files/downloads/llbmc-bench-1.1.tgz for running with KLEE, e.g., replaced LLBMC API calls with the corresponding KLEE API calls.

- **join** - Examples for testing `klee_join` API. This directory also contains
academic programs focusing on program equivalence analysis, with an
example taken from [KLEE OSDI paper 2008]
(https://www.doc.ic.ac.uk/~cristic/papers/klee-osdi-08.pdf).

- **coreutils** - Examples of 89 stand-alone programs in the GNU Coreutils-6.10 utility suite. In this version, KLEE was able to find some bugs and they are reported in the [OSDI Paper](https://www.doc.ic.ac.uk/~cristic/papers/klee-osdi-08.pdf). The `coreutils` directory contains `coreutils-6.10` subdirectory of GNU Coreutils 6.10.

- **utils** - Scripts and other utilities.

Running
-------

To run any of the examples, first you need to execute the provided `configure` script. In particular, please set the following `configure` options:
- The following options are relevant for all categories of examples:
```
  --with-klee             KLEE installation directory (defaults to
                          /usr/local/lib/tracerx)
  --with-z3               The directory of Z3 (defaults to /usr/local/lib/z3)
  --with-stp              The directory of STP (defaults to /usr/local)
```
- The following option is relevant only for running **join** examples
```
  --with-clpr             The directory of CLP(R) (defaults to /usr/local)
```
- The following options are relevant only for running **coreutils** examples
```
  --with-wllvm            The source directory of whole-program-llvm (defaults
                          to /usr/local/lib/whole-program-llvm)
  --with-texinfo          GNU texinfo 4.13 installation directory, i.e., the
                          info utility should be under the bin subdirectory of
                          the specified directory. Coreutils 6.10 requires GNU
                          texinfo no later than 4.13.
```
- The following option is relevant for both **coreutils** and **scalability** examples
```
  --with-llbmc            LLBMC installation directory, i.e., the llbmc
                          executable should be under the bin subdirectory of
                          the specified directory (defaults to /usr/local).
```

Running examples other than *join* and *coreutils*
--------------------------------------------------

Instruction on running the examples in the `join` and `coreutils` directories can be found later in this document. Please first run the `configure` script as instructed above. Then to run the the example(s) in a particular directory, say `basic`, change your current directory to the `basic` directory.

The `Makefile` in each directory will create KLEE output directories `<example-name>.klee` which also contains the `.dot` files, and also `<example-name>.inputs` files that show the input values for each test.

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

   2. You may/may not need an older version of GNU texinfo. The build does not work with texinfo 5.2, but known to work with 4.13. Texinfo 4.13 can be found [here](http://ftp.gnu.org/gnu/texinfo/texinfo-4.13.tar.gz).

- Do not forget to run the `configure` script as instructed above, then:
   1. `cd coreutils`
   2. Run `make` in any of these ways:
       - `make build` - To build Coreutils 6.10 twice: one with LLVM (in `coreutils/coreutils-6.10/obj-llvm/src`) and another with GCOV (in `coreutils/coreutils-6.10/obj-gcov/src`) without running KLEE.
       - Just `make` - Runs the test-case generation on all programs: it will build Coreutils 6.10 if this is not done already.
       - `make <program_name>.klee` - Runs the test-case generation on `<program_name>`: it will build Coreutils 6.10 if this is not done already. Here, `<program_name>` is one of the Coreutils programs whose executable file is found as `coreutils/coreutils-6.10/obj-llvm/src/<program_name>`. The output will be the result of Tracer-X KLEE run on the program and its coverage information.
       - `make <program_name>.stpklee` - Runs the test-case generation on `<program_name>` similar to `make <program_name>.klee`, however, Tracer-X KLEE will be invoked with `--select-solver=stp` which disables interpolation and uses STP, resulting in standard KLEE run using STP.

- Note that using `make`, the test cases generated by Tracer-X KLEE will be in `coreutils/<program_name>.klee` and the test cases generated by KLEE/STP will be in `coreutils/<program_name>.stpklee`.

Stress testing using **exp-201609**
-------------------------------

This will run **coreutils** and **scalability** examples with KLEE, Tracer-X KLEE, and LLBMC, and collect data for presentation.

- Needless to say, one need to first run the `configure` script as instructed above.

- For running experiment exp-201609 in Coreutils 6.10 program, please go to coreutils directory (`cd coreutils`) and run `make exp-201609`. The experiment will run different kinds of settings which can be seen in %.klee1, %.klee2, %.tracerx1, %.tracerx2, %.tracerx3, %.tracerx4 on selected coreutils programs under exp-201609 target. To collect all the experiment results into csv file, please run `make csv-exp-201609`.

- For running experiment exp-201609 under Scalability folder, please go to coreutils directory (`cd scalability`) and run `make exp-201609`. To collect all the experiment results into csv file, please run `make csv-exp-201609`. 
