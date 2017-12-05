#!/usr/bin/env bash
#
# Script to compute coverage, with a feature to compute coverage from
# some point in time after KLEE started executing.
#
# Copyright 2017 National University of Singapore
#
# Environment variables that can be set externally include:
#
# EXTRA_CFLAGS    - Extra CFLAGS options
# EXTRA_LDFLAGS   - Extra LDFLAGS options

PROGRAM=$1
OUTPUT_DIR=$2
TIME_SINCE=$3

if [ -z "$OUTPUT_DIR" ] ; then
    echo "Please specify program and extension"
    exit 1
fi
if [ ! -e "$OUTPUT_DIR/test000001.ktest" ] ; then
    echo "Specified output directory does not contain tests"
    ( echo -n 0 > $OUTPUT_DIR/LcovLog.txt )
    ( echo -n 0 > $OUTPUT_DIR/SLocCountLog.txt )
    exit 0
fi

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source $SCRIPT_DIR/../environ.sh

MAX_TIME=
if [ ! -z "$TIME_SINCE" ] ; then
    START_TIME=`stat --format="%Z" $OUTPUT_DIR/test000001.ktest | tr -d '\n'`
    MAX_TIME=`expr $START_TIME + $TIME_SINCE`
fi

IMAGEMAGICK_DIR=$SCRIPT_DIR/../imagemagick/ImageMagick-7.0.5-9

IMAGEMAGICK_COV_DIR=$IMAGEMAGICK_DIR/obj-cov

echo =================================================================
echo Running generated tests to compute coverage ...
echo =================================================================
OUTPUT_COV_DIR=$OUTPUT_DIR/cov
rm -rf $OUTPUT_COV_DIR
mkdir $OUTPUT_COV_DIR
rm -f `find ${IMAGEMAGICK_COV_DIR} -name "*.gcda"`
(
    cd $IMAGEMAGICK_COV_DIR/utilities/.libs
    TEST_FILES=$OUTPUT_DIR/*.ktest
    for KTEST in $TEST_FILES ; do
	if [ ! -z "$MAX_TIME" ] ; then
	    TIME=`stat --format="%Z" $KTEST | tr -d '\n'`
	    if [ $MAX_TIME -gt $TIME ] ; then
		( LD_LIBRARY_PATH=$KLEE_HOME/lib KTEST_FILE=$KTEST KLEE_REPLAY_TIMEOUT=$KLEE_REPLAY_TIMEOUT $KLEE_REPLAY $PROGRAM $KTEST )
	    fi
	else
	    ( LD_LIBRARY_PATH=$KLEE_HOME/lib KTEST_FILE=$KTEST KLEE_REPLAY_TIMEOUT=$KLEE_REPLAY_TIMEOUT $KLEE_REPLAY $PROGRAM $KTEST )
	fi
    done
)

(
    cd $IMAGEMAGICK_COV_DIR

    LINE_COVERAGE_TOTAL=0

    LCOV_OBJECTS=`find . -name "*.gcda"`

    LCOV_SOURCES=""

    LOC_TOTAL=0

    for LCOV_OBJ in $LCOV_OBJECTS ; do
	LCOV_BASENAME=$(basename "$LCOV_OBJ")
	LCOV_FILENAME=${LCOV_BASENAME%.*}
	LCOV_DIRNAME=$(dirname "$LCOV_OBJ")
	
	OUTPUT_LCOV_DIRNAME=$OUTPUT_COV_DIR/$LCOV_DIRNAME
	
	OUTPUT_LCOV_FILENAME=$OUTPUT_LCOV_DIRNAME/$LCOV_FILENAME.cov
	
	echo Saving llvm-cov output in $OUTPUT_LCOV_FILENAME
	
	if [ ! -d $OUTPUT_LCOV_DIRNAME ] ; then
	    mkdir $OUTPUT_LCOV_DIRNAME
	fi
	
	cd $IMAGEMAGICK_COV_DIR/$LCOV_DIRNAME
	
	llvm-cov -gcno=./$LCOV_FILENAME.gcno -gcda=./$LCOV_FILENAME.gcda > $OUTPUT_LCOV_FILENAME
	
	NEW_SRC_LIST=`cat $OUTPUT_LCOV_FILENAME | grep '0:Source:' | sed s/-://g | sed s/0:Source://g`
	for NEW_SRC_FILE in $NEW_SRC_LIST ; do
	    LCOV_SOURCES="$LCOV_SOURCES $IMAGEMAGICK_COV_DIR/$LCOV_DIRNAME/$NEW_SRC_FILE"
	done
	
	LINE_COVERAGE=`cat $OUTPUT_LCOV_FILENAME | grep '^[[:space:]]*[[:digit:]]\+' | wc -l`
	LINE_NON_COVERAGE=`cat $OUTPUT_LCOV_FILENAME | grep '^[[:space:]]*#####:' | wc -l`
	LINE_COVERAGE_TOTAL=`expr $LINE_COVERAGE_TOTAL + $LINE_COVERAGE`
	LOC_TOTAL=`expr $LOC_TOTAL + $LINE_COVERAGE + $LINE_NON_COVERAGE`
    done

    ( echo -n $LINE_COVERAGE_TOTAL > $OUTPUT_DIR/LcovLog.txt )

    ( echo -n $LOC_TOTAL > $OUTPUT_DIR/SLocCountLog.txt )

)
