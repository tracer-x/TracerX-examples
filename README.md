Simple examples for running with Tracer-X KLEE
----------------------------------------------

Copyright 2015-2017 National University of Singapore. See `LICENSE.md` for license information.

This software includes third-party software, including some sample programs are from LLBMC 2013.1 distribution modified for running with KLEE, GNU Coreutils 6.10, ImageMagick 7.0.5-9, and portions of libPNG. Their license information is included in the `license/LLBMC_LICENSE`, `license/COPYING`, `license/IMAGEMAGICK_LICENSE` and `license/LIBPNG_LICENSE`.

LLBMC 2013.1 is Copyright (c) 2010-2013 Stephan Falke, Florian Merz, Carsten Sinz Karlsruhe Institute of Technology (KIT), Germany. All rights reserved.  Coreutils 6.10 is Copyright (C) 1984-2008 Free Software Foundation. Refer to `license/IMAGEMAGICK_NOTICE` for the copyright notice of ImageMagick 7.0.5-9 and `license/LIBPNG_LICENSE` for the copyright notice of libPNG.

Each directory except **include** and **utils** contains a suite of simple examples.

- **basic**  - Basic examples. 

- **binary-chop** - Examples which test the binary chop algorithm for WCET analysis, including `nsichneu.c` and `statemate.c` which are also used to test scalability.

- **scalability** - Examples that tests scalability, including `Regexp.c`, an example from KLEE tutorial at http://klee.github.io/tutorials.

- **include** - Include files for running with various tools.

- **coreutils** - Examples of 89 stand-alone programs in the GNU Coreutils-6.10 utility suite. In this version, KLEE was able to find some bugs and they are reported in the [OSDI Paper](https://www.doc.ic.ac.uk/~cristic/papers/klee-osdi-08.pdf). The `coreutils` directory contains `coreutils-6.10` subdirectory of GNU Coreutils 6.10.

- **imagemagick** - ImageMagick 7.0.5-9

- **utils** - Scripts and other utilities. This contains, among others, `cav17-coreutils.sh` and `cav17-scalability.sh` for reproducing the experimental results of our CAV '17 paper submission.

The following directories are work in progress.

- **abstract** - Examples for testing `klee_abstract` API.

- **join** - Examples for testing Tracer-X `klee_join` API. This directory also contains
academic programs focusing on program equivalence analysis, with an
example taken from [KLEE OSDI paper 2008]
(https://www.doc.ic.ac.uk/~cristic/papers/klee-osdi-08.pdf).

- **memleak** - C programs with memory leak.

- **taint** - Assortment of examples extracted from known vulnerabilities: some may require KLEE API introduced in [a version of KLEE with taint propagation](https://github.com/feliam/klee-taint.git).

Configuring
-----------

To run any of the examples, first you need to execute the provided `configure` script. In particular, please set the following `configure` options:
- The following options are relevant for all categories of examples:
```
  --with-klee             KLEE installation directory (defaults to
                          /usr/local/lib/tracerx)
  --with-z3               The directory of Z3 (defaults to /usr/local/lib/z3)
  --with-stp              The directory of STP (defaults to /usr/local)
```
- The following option is relevant only for running with **join** examples
```
  --with-clpr             The directory of CLP(R) (defaults to /usr/local)
```
- The following options are relevant only for running with **coreutils** examples
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

Running with example programs other than *join*, *coreutils*, and *scalability*
-------------------------------------------------------------------------------

Instruction on running with the examples in the `join`, `coreutils`, and `scalability` directories can be found later in this document. Please first run the `configure` script as instructed above. Then to run the the example(s) in a particular directory, say `basic`, change your current directory to the `basic` directory.

The `Makefile` in each directory will create KLEE output directories `<example-name>.tx` which also contains the `.dot` files, and also `<example-name>.inputs` files that show the input values for all of the generated tests.

Sample usages:
- To run a single example, e.g., addition_safe1.c in the basic directory with KLEE using Z3 solver and interpolation:

  `make addition_safe1.tx`

  Optionally, add `ENABLE_COVERAGE=ON` to the `make` command to enable coverage computation. If the file `subsumption.dat` exists, this would also perform a regression test on the number of subsumptions compared to reference data in `subsumption.dat`.

- To run all examples with KLEE using Z3 solver and interpolation:

  `make`

  This is the same as executing `make <example_name>.tx` for all examples. Optionally, add `ENABLE_COVERAGE=ON` to the `make` command to enable coverage computation.

- To run a single example, e.g., addition_safe1.c in the basic directory using Z3 solver but without interpolation:

  `make addition_safe1.klee`

  Optionally, add `ENABLE_COVERAGE=ON` to the `make` command to enable coverage computation.

- To run a single example, e.g., addition_safe1.c in the basic directory using STP solver and without interpolation:

  `make addition_safe1.stpklee`

  Optionally, add `ENABLE_COVERAGE=ON` to the `make` command to enable coverage computation.

- You can also execute LLBMC to analyze `addition_safe1.c` after properly configuring this repository using `--with-llbmc`. The execution can be done as in the following example:

  `make addition_safe1.llbmc`

- To build an LLVM IR file of `addition_safe1.c`:

  `make addition_safe1.ll`

- To clean the directory:

  `make clean`

Running with *join* examples
----------------------------

The examples in the `join` subdirectory requires Tracer-X KLEE to be compiled with CLP(R) 1.2l support. The `Makefile` tests can be run in the following way:

- For running Tracer-X KLEE with `join1.c` to test the ability of `-use-clpr` option to load multiple CLP(R) files.

  `make test-use-clpr`

- For running Tracer-X KLEE with `join2.c` to actually test the subsumption ability of Tracer-X KLEE with `klee_join`.

  `make test-join`

- There are other programs such as `count.c` and `sum.c` in the `join` directory. Please consult `join/Makefile`, which contains `test-*` targets to run them.

Running with *coreutils* or *scalability* examples
--------------------------------------------------

1. Run the `configure` script as instructed above.
2. For *coreutils*, build it as follows:
   - *Prerequisites:* 
     1. `whole-program-llvm`. This can be obtained by cloning it from GitHub, i.e.: `git clone https://github.com/travitch/whole-program-llvm.git`
     2. You may/may not need an older version of GNU texinfo. The build does not work with texinfo 5.2, but known to work with 4.13. Texinfo 4.13 can be found [here](http://ftp.gnu.org/gnu/texinfo/texinfo-4.13.tar.gz).
   - *Steps:*
     1. `cd coreutils`
     2. Run `make build`. This builds Coreutils 6.10 twice: one with for producing whole-program bitcode in `coreutils/coreutils-6.10/obj-llvm/src`, and another with instrumentation for measuring coverage with `llvm-cov` in `coreutils/coreutils-6.10/obj-cov/src`.
3. Set open file limits to 65536 in the following way: `ulimit -n 65536`. The number 65536 seems to work. Please note that this may not work depending on whether the number exceeds your hard limit. You can check the hard limit via `ulimit -H -n`.
4. `cd coreutils` or `cd scalability`
5. Run `make` in any of the following ways:
    - Just `make` - Runs the test-case generation on all programs: in case of *coreutils*, this will build Coreutils 6.10 if this is not done already.
    - `make <program_name>.tx` - Runs the test-case generation on `<program_name>`: it will build Coreutils 6.10 if this is not done already. Here, `<program_name>` is one of the Coreutils programs whose executable file is found as `coreutils/coreutils-6.10/obj-llvm/src/<program_name>`. The output will be the result of Tracer-X KLEE run on the program with Z3 solver backend and interpolation, and its coverage information .The test cases are saved in `<program_name>.tx` directory.
    - `make <program_name>.klee` - Runs the test-case generation on `<program_name>` similar to `make <program_name>.tx`, however, Tracer-X KLEE will be invoked with `-solver-backend=z3` and `-no-interpolation` to disable interpolation. This makes the run equivalent to running KLEE with `-solver-backend=z3`. The test cases are saved in `<program_name>.klee` directory.
    - `make <program_name>.stpklee` - Runs the test-case generation on `<program_name>` similar to `make <program_name>.klee`, however, Tracer-X KLEE will be invoked with `-solver-backend=stp` which disables interpolation and uses STP, resulting in standard KLEE run using STP. The test cases are saved in `<program_name>.stpklee` directory.
    - `make <program_name>.llbmc` - Runs LLBMC on `<program_name>`.
    - `make experiment.csv` or `make llbmc-experiment.csv`.
        * These are for executing with the example programs using KLEE, Tracer-X KLEE, and LLBMC, and collecting data for presentation. The targets will produce `experiment.csv` and `llbmc-experiment.csv` comma-separated values files, respectively, depending on which one was invoked. `experiment.csv` target will produce both `experiment.csv` and `small-experiment.csv`, which is the version with less data columns.
        * For **coreutils** benchmark, `llbmc-experiment.csv` target will also produce `experiment.csv` (and `small-experiment.csv`) for the data for Tracer-X and KLEE (Z3 and STP) runs. This is because LLBMC can only be run on a smaller subset of Coreutils 6.10 programs, and on bitcode generated from the source of the `main` function only without linking with external files and libraries (libc). As such, for a more fair comparison, Tracer-X and KLEE must also be executed on the same bitcode.
        * The experiments are run under different kinds of settings which can be seen in %.klee1, %.klee2, %.tx1, %.tx2, %.tx3, %.tx4, %.tx5, and %.tx6 targets defined in the `coreutils/Makefile` and `scalability/Makefile`, on the selected coreutils programs specified using the `EXPERIMENT_SET` variable in `coreutils/Makefile` and `scalability/Makefile`.

Note that by default, line coverage computation is performed using `llvm-cov`. To prevent, this, add `ENABLE_COVERAGE=OFF` to the `make` command, for example: `make ENABLE_COVERAGE=OFF Regexp.tx`.



