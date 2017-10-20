#!/usr/bin/env bash
# Coreutils experiments for FMCAD '17 submission
#
# Here we only run LLBMC to add LLBMC numbers to CAV '17 KLEE and
# Tracer-X numbers.
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COREUTILS_DIR=$SCRIPT_DIR/../coreutils

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

cd $COREUTILS_DIR
make clean

###################################################################
# cut
###################################################################

export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 5 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make cut.klee1 ; \
    mv cut.klee1 cut.klee101 ; \
    make cut.tx1 ; \
    mv cut.tx1 cut.tx101 \
)

export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 6 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make cut.klee1 ; \
    mv cut.klee1 cut.klee102 ; \
    make cut.tx1 ; \
    mv cut.tx1 cut.tx102 \
)

export PROGRAM_OPTIONS="-b -sym-arg 3 -sym-stdin 7 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make cut.klee1 ; \
    mv cut.klee1 cut.klee103 ; \
    make cut.tx1 ; \
    mv cut.tx1 cut.tx103 \
)

export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/cut.llbmc102
export PROGRAM_OPTIONS="-b xxx"
make cut.llbmc

###################################################################
# basename
###################################################################

export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 3 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make basename.klee1 ; \
    mv basename.klee1 basename.klee102 ; \
    make basename.tx1 ; \
    mv basename.tx1 basename.tx102 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/basename.llbmc102
export PROGRAM_OPTIONS="xxxxxxxxxx xxx xxx"
make basename.llbmc

export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 4 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make basename.klee1 ; \
    mv basename.klee1 basename.klee103 ; \
    make basename.tx1 ; \
    mv basename.tx1 basename.tx103 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/basename.llbmc103
export PROGRAM_OPTIONS="xxxxxxxxxx xxxx xxxx"
make basename.llbmc

export PROGRAM_OPTIONS="--sym-args 0 1 10 --sym-args 0 2 5 --sym-files 1 8 -sym-stdin 8 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make basename.klee1 ; \
    mv basename.klee1 basename.klee104 ; \
    make basename.tx1 ; \
    mv basename.tx1 basename.tx104 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/basename.llbmc104
export PROGRAM_OPTIONS="xxxxxxxxxx xxxxx xxxxx"
make basename.llbmc


###################################################################
# pathchk
###################################################################

export PROGRAM_OPTIONS="-sym-arg 13 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make pathchk.klee1 ; \
    mv pathchk.klee1 pathchk.klee101 ; \
    make pathchk.tx1 ; \
    mv pathchk.tx1 pathchk.tx101 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc101
export PROGRAM_OPTIONS="xxxxxxxxxxxxx"
make pathchk.llbmc

export PROGRAM_OPTIONS="-sym-arg 14 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make pathchk.klee1 ; \
    mv pathchk.klee1 pathchk.klee102 ; \
    make pathchk.tx1 ; \
    mv pathchk.tx1 pathchk.tx102 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc102
export PROGRAM_OPTIONS="xxxxxxxxxxxxxx"
make pathchk.llbmc

export PROGRAM_OPTIONS="-sym-arg 15 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make pathchk.klee1 ; \
    mv pathchk.klee1 pathchk.klee103 ; \
    make pathchk.tx1 ; \
    mv pathchk.tx1 pathchk.tx103 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc103
export PROGRAM_OPTIONS="xxxxxxxxxxxxxxx"
make pathchk.llbmc

export PROGRAM_OPTIONS="-sym-arg 16 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make pathchk.klee1 ; \
    mv pathchk.klee1 pathchk.klee104 ; \
    make pathchk.tx1 ; \
    mv pathchk.tx1 pathchk.tx104 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc104
export PROGRAM_OPTIONS="xxxxxxxxxxxxxxxx"
make pathchk.llbmc

export PROGRAM_OPTIONS="-sym-arg 17 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make pathchk.klee1 ; \
    mv pathchk.klee1 pathchk.klee105 ; \
    make pathchk.tx1 ; \
    mv pathchk.tx1 pathchk.tx105 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc105
export PROGRAM_OPTIONS="xxxxxxxxxxxxxxxxx"
make pathchk.llbmc

export PROGRAM_OPTIONS="-sym-arg 18 --sym-stdout"
(\
    cd $COREUTILS_DIR ; \
    make pathchk.klee1 ; \
    mv pathchk.klee1 pathchk.klee106 ; \
    make pathchk.tx1 ; \
    mv pathchk.tx1 pathchk.tx106 \
)
export LLBMC_OUTPUT_DIR=$COREUTILS_DIR/pathchk.llbmc106
export PROGRAM_OPTIONS="xxxxxxxxxxxxxxxxxx"
make pathchk.llbmc

###################################################################
# LLBMC table
###################################################################

export OUTPUT_DIR_SET="$COREUTILS_DIR/cut.llbmc102 $COREUTILS_DIR/basename.llbmc102 $COREUTILS_DIR/basename.llbmc103 $COREUTILS_DIR/basename.llbmc104 $COREUTILS_DIR/pathchk.llbmc101 $COREUTILS_DIR/pathchk.llbmc102 $COREUTILS_DIR/pathchk.llbmc103 $COREUTILS_DIR/pathchk.llbmc104 $COREUTILS_DIR/pathchk.llbmc105 $COREUTILS_DIR/pathchk.llbmc106"
make llbmc-experiment.csv.only
	      
cd $SCRIPT_DIR
