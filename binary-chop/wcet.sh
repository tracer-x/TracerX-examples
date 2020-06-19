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

export EXPERIMENT_TYPE_SET=".tx1"
export ENABLE_COVERAGE=OFF
if [[ $3 == "-w" ]]; then
	export INTERPOLATION='WP'
else
	export INTERPOLATION='DEL'
fi

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
	cp src/"$BENCHMARK".c "$BENCHMARK".c 
	sed -i 's/int main() {/void tracerx_check() { printf(\"Timing of Path:%d\\n\",wcet); klee_assert(wcet <= '$CURRENT_BOUND');}\nint main() {/g' "$BENCHMARK".c  
	cp llvm_annotate/* . 
	./Annotator.sh "$BENCHMARK"
	if [[ $3 == "-w" ]]; then
        	#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee -exit-on-error -use-query-log=all:pc,all:smt2 -search=dfs -wp-interpolant -max-memory=32000 -max-time=3600 -only-output-states-covering-new -solver-backend=z3 -output-dir=$WCET_DIR/"$BENCHMARK".tx "$BENCHMARK".bc &> output.txt
  		klee --max-memory=32000 --max-time=3600 -solver-backend=z3  -exit-on-error --search=dfs -allow-external-sym-calls --watchdog -dump-states-on-halt=0 -wp-interpolant -no-output -output-dir=$WCET_DIR/"$BENCHMARK".tx ${BENCHMARK}.bc &> output.txt
        	
	else
  		#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee -exit-on-error -use-query-log=all:pc,all:smt2 -search=dfs -max-memory=32000 -max-time=3600 -only-output-states-covering-new -solver-backend=z3 -output-dir=$WCET_DIR/"$BENCHMARK".tx "$BENCHMARK".bc &> output.txt
  		klee --max-memory=32000 --max-time=3600 -solver-backend=z3  -exit-on-error --search=dfs -allow-external-sym-calls --watchdog -dump-states-on-halt=0 -no-output -output-dir=$WCET_DIR/"$BENCHMARK".tx ${BENCHMARK}.bc &> output.txt
	fi
	#cat output.txt 
	printf "Instructions Count: "
	klee-stats "$BENCHMARK".tx | sed '4q;d' | cut -d '|' -f3  | tr -d '\n' | tr -d ' ' 
	INSTRUCTION_COUNT=$(klee-stats "$BENCHMARK".tx | sed '4q;d' | cut -d '|' -f3  | tr -d '\n' | tr -d ' ' )
	printf "\nAnalysis time: "
	klee-stats "$BENCHMARK".tx | sed '4q;d' | cut -d '|' -f4  | tr -d '\n' | tr -d ' ' 
	ANALYSIS_TIME=$(klee-stats "$BENCHMARK".tx | sed '4q;d' | cut -d '|' -f4  | tr -d '\n' | tr -d ' ' )
	if ! grep -qF "ERROR:" "$BENCHMARK".tx/messages.txt; then
	    printf "\n$green\n" "Bound is safe"	
	    echo
	    UPPER_BOUND=$[$CURRENT_BOUND]
	    COMPLETED_PATHS_TEMP=$(grep 'KLEE: done:     program exit paths = [0-9][0-9]*' output.txt | tail -1)
	    COMPLETED_PATHS=${COMPLETED_PATHS_TEMP:37}
	    SUBSUMED_PATHS_TEMP=$(grep 'KLEE: done:     subsumed paths = [0-9][0-9]*' output.txt | tail -1)
	    SUBSUMED_PATHS=${SUBSUMED_PATHS_TEMP:33}
	    if [[ $3 == "-w" ]]; then
		printf "\nSlack Pushup: "
		grep 'WCET Pushup:' output.txt | cut -d : -f 2 | xargs basename
		SLACK=$(grep 'WCET Pushup:' output.txt | cut -d : -f 2 | xargs basename)
	    else
		printf "\nSlack Pushup: 0"
		SLACK=0
	    fi
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
		rm -R "$BENCHMARK".tx
		rm "$BENCHMARK".c
		rm "$BENCHMARK"*
		rm Annotator* clang.tmp annotate.tmp 
		rm output.txt
	        break
	    else
	        if [ -n "$SLACK" ] && [ "$SLACK" -eq "$SLACK" ] 2>/dev/null; then
	        	UPPER_BOUND=$[$UPPER_BOUND-$SLACK]
	        fi
	        CURRENT_BOUND=$[($UPPER_BOUND + $LOWER_BOUND) / 2]
	    fi
	else
	    COMPLETED_PATHS='-'
	    SUBSUMED_PATHS='-'
	    COUNTER_EXAMPLE=$(grep 'Timing of Path:[0-9][0-9]*' output.txt | tail -1)
	    printf "\nCounter Example WCET:"
	    echo $[${COUNTER_EXAMPLE:15}]
	    printf "$red\n" "Bound is not safe"
	    echo	
	    LOWER_BOUND=$[${COUNTER_EXAMPLE:15}]
	    CURRENT_BOUND=$[($UPPER_BOUND + $LOWER_BOUND) / 2]
	    IS_SAFE="No (${COUNTER_EXAMPLE:15})"
	fi	
	echo "$ROUND,$BENCHMARK,\"$OLD_LOWER_BOUND-$OLD_UPPER_BOUND\",$OLD_CURRENT_BOUND,$IS_SAFE,$PRECISION,$ANALYSIS_TIME,$INSTRUCTION_COUNT,$COMPLETED_PATHS,$SUBSUMED_PATHS" >> result-$BENCHMARK.csv
	ROUND=$[$ROUND+1]
	rm -R "$BENCHMARK".tx
	rm "$BENCHMARK"*
	#rm Annotator* clang.tmp annotate.tmp
	rm output.txt
done
echo ",,,,,,,," >> result-$BENCHMARK.csv

