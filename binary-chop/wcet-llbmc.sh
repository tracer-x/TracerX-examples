#!/usr/bin/env bash
#
# WCET experiments for RTAS'20 submission. 
#
# Copyright 2019 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

WCET_DIR=$SCRIPT_DIR

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

red='\e[1;31m%s\e[0m\n'
green='\e[1;32m%s\e[0m\n'
yellow='\e[1;33m%s\e[0m\n'
blue='\e[1;34m%s\e[0m\n'
magenta='\e[1;35m%s\e[0m\n'
cyan='\e[1;36m%s\e[0m\n'

export INTERPOLATION='LLBMC'

# Adding the target in benchmarks
export BENCHMARK=$1
export UPPER_BOUND=$2

# Write header information
echo "Round,Benchmark,Known Lower/Upper Bound,Tested Bound,Result,Precision,Analysis Time (sec),Instruction Count,Completed Paths,Subsumed Paths" >> result-$BENCHMARK.csv

i=0
export ROUND=1
export CURRENT_BOUND=$UPPER_BOUND
export LOWER_BOUND=1
printf "\n\nAnalysing $BENCHMARK:\n" 
while true; do
	echo "Adding bound $BOUND to $BENCHMARK." 
	echo "UPPER BOUND: "$UPPER_BOUND
        echo "CURRENT BOUND: "$CURRENT_BOUND
        echo "LOWER BOUND: "$LOWER_BOUND
	OLD_UPPER_BOUND=$UPPER_BOUND
	OLD_CURRENT_BOUND=$CURRENT_BOUND
	OLD_LOWER_BOUND=$LOWER_BOUND
	PRECISION=$(bc -l <<< "scale = 2;100*(1-($UPPER_BOUND-$LOWER_BOUND)/(sqrt($UPPER_BOUND^2+$LOWER_BOUND^2)))" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
	echo "Precision: "$PRECISION
	cp llbmc-src/"$BENCHMARK".c "$BENCHMARK".c 
	sed -i 's/int main() {/void tracerx_check() { printf(\"Timing of Path:%d\\n\",wcet);  __llbmc_assert(wcet <= '$CURRENT_BOUND');}\nint main() {/g' "$BENCHMARK".c  
	cp llvm_annotate/* . 
	./Annotator.sh "$BENCHMARK"
	timeout 3600 time llbmc --no-overflow-checks -max-loop-iterations=100 -max-function-call-depth=100 --ignore-missing-function-bodies ${BENCHMARK}.bc &> ${BENCHMARK}-result.txt
	#cat ${BENCHMARK}-result.txt
	printf "Analysis time: "
	grep 'user' "$BENCHMARK"-result.txt | cut -d 'u' -f 1 
	ANALYSIS_TIME=$(grep 'user' "$BENCHMARK"-result.txt | cut -d 'u' -f 1 )
	if ! grep -qF "Error detected." "$BENCHMARK"-result.txt; then
	    printf "\n$green\n" "Bound is safe"	
	    echo
	    UPPER_BOUND=$[$CURRENT_BOUND]
	    IS_SAFE="Safe"
	    if  [ $(echo " ($UPPER_BOUND-$LOWER_BOUND)/sqrt(($UPPER_BOUND^2+$LOWER_BOUND^2)/2) <= 0.02" | bc -l) -eq 1 ] || [ "$UPPER_BOUND" -eq 1 ] ; then
 		echo
	       	echo "Analysis has finished:"
	        echo "UPPER BOUND: "$UPPER_BOUND
	        echo "LOWER BOUND: "$LOWER_BOUND
		echo "Precision: " 
		echo $PRECISION
		echo "$ROUND,$BENCHMARK,\"$OLD_LOWER_BOUND-$OLD_UPPER_BOUND\",$OLD_CURRENT_BOUND,$IS_SAFE,$PRECISION,$ANALYSIS_TIME,$INSTRUCTION_COUNT,$COMPLETED_PATHS,$SUBSUMED_PATHS" >> result-$BENCHMARK.csv
		PRECISION=$(bc -l <<< "scale = 2;100*(1-($UPPER_BOUND-$LOWER_BOUND)/sqrt(($UPPER_BOUND^2+$LOWER_BOUND^2)/2))" | grep -Eo '[+-]?[0-9]+([.][0-9]+)?')
		echo "$INTERPOLATION,$BENCHMARK,\"$LOWER_BOUND-$UPPER_BOUND\",-,Safe,$PRECISION,-,-" >> result-$BENCHMARK.csv
		rm "$BENCHMARK".c
		rm Annotator* clang.tmp annotate.tmp 
	        break
	    else
	        CURRENT_BOUND=$[($UPPER_BOUND + $LOWER_BOUND) / 2]
	    fi
	else
	    printf "$red\n" "Bound is not safe"
	    echo	
	    LOWER_BOUND=$CURRENT_BOUND
	    CURRENT_BOUND=$[($UPPER_BOUND + $LOWER_BOUND) / 2]
	    IS_SAFE="No (${COUNTER_EXAMPLE:15})"
	fi
	echo "$ROUND,$BENCHMARK,\"$OLD_LOWER_BOUND-$OLD_UPPER_BOUND\",$OLD_CURRENT_BOUND,$IS_SAFE,$PRECISION,$ANALYSIS_TIME,$INSTRUCTION_COUNT,$COMPLETED_PATHS,$SUBSUMED_PATHS" >> result-$BENCHMARK.csv
	ROUND=$[$ROUND+1]
	#rm Annotator* clang.tmp annotate.tmp
done
echo ",,,,,,,," >> result-$BENCHMARK.csv

