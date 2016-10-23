#!/usr/bin/env bash
# For rebuilding GNU Coreutils not from scratch
#
# Copyright 2016 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COREUTILS_DIR=$SCRIPT_DIR/../coreutils/coreutils-6.10/obj-llvm

source $SCRIPT_DIR/../environ.sh

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH
(cd $COREUTILS_DIR ; make )
rm -f $COREUTILS_DIR/src/*.gcov
( cd $COREUTILS_DIR/src; \
                EXEC_LIST=`find . -executable -type f | sed 's/.\/groups//'` ; \
                for EXEC_FILE in $EXEC_LIST ; do \
                        $WHOLE_PROGRAM_LLVM/extract-bc $EXEC_FILE ; \
                done \
        )

