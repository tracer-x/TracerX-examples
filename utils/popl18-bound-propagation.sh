#!/usr/bin/env bash
#
# WCET experiments for POPL '18 submission. 
#
# Copyright 2017 National University of Singapore

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source $SCRIPT_DIR/../environ.sh
WCET_DIR=$SCRIPT_DIR/../binary-chop

unset C_INCLUDE_PATH
unset CPLUS_INCLUDE_PATH

red='\e[1;31m%s\e[0m\n'
green='\e[1;32m%s\e[0m\n'
yellow='\e[1;33m%s\e[0m\n'
blue='\e[1;34m%s\e[0m\n'
magenta='\e[1;35m%s\e[0m\n'
cyan='\e[1;36m%s\e[0m\n'

mv result.csv result_old.csv

export EXPERIMENT_SET="expint"  # nsichneu_small nsichneu  cnt Regexp7 Regexp8 Regexp9 Regexp10 Regexp15 statemate ud
export EXPERIMENT_TYPE_SET=".tx1"
export ENABLE_COVERAGE=OFF

# Adding the target in benchmarks
export BENCHMARKS=$(echo $EXPERIMENT_SET | tr " " "\n")

echo "Round,Benchmark,Upper Bound,Tested Bound,Lower Bound,Is Safe,Precision,Analysis Time (sec),Instruction Count" >> result.csv

for BENCHMARK in $BENCHMARKS
do
	export ROUND=1
	export UPPER_BOUND=1000
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
		echo "Precision: " 
		PRECISION=$(bc -l <<< "scale = 2;100*(1-($UPPER_BOUND-$LOWER_BOUND)/sqrt(($UPPER_BOUND^2+$LOWER_BOUND^2)/2))")
		echo "scale = 2;100*(1-($UPPER_BOUND-$LOWER_BOUND)/sqrt(($UPPER_BOUND^2+$LOWER_BOUND^2)/2));scale=2" | bc -l
		cat src/"$BENCHMARK".pre > "$BENCHMARK".c 
		echo "char _bound[$CURRENT_BOUND];"  >> "$BENCHMARK".c  
		cat src/"$BENCHMARK".post >> "$BENCHMARK".c   
		make "$BENCHMARK".tx 2> output.txt > output.txt 
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
		    if  [ $(echo " ($UPPER_BOUND-$LOWER_BOUND)/sqrt(($UPPER_BOUND^2+$LOWER_BOUND^2)/2) <= 0.01" | bc -l) -eq 1 ] || [ "$UPPER_BOUND" -eq 1 ] ; then
	  		echo
		       	echo "Analysis has finished:"
		        echo "UPPER BOUND: "$UPPER_BOUND
		        echo "LOWER BOUND: "$LOWER_BOUND
			echo "Precision: " 
			echo "scale = 2;100*(1-($UPPER_BOUND-$LOWER_BOUND)/sqrt(($UPPER_BOUND^2+$LOWER_BOUND^2)/2));scale=2" | bc -l
			rm -R "$BENCHMARK".tx
			rm "$BENCHMARK".c
			rm output.txt
		        break
		    else
  		        CURRENT_BOUND=$[($UPPER_BOUND + $LOWER_BOUND) / 2]
		    fi
		    IS_SAFE="Y"
		else
		    COUNTER_EXAMPLE=$(grep 'Timing of Path:[0-9][0-9]*' output.txt | tail -1)
		    printf "\nCounter Example Time:"
		    echo $[${COUNTER_EXAMPLE:15}]
		    printf "$red\n" "Bound is not safe"
		    echo	
  		    LOWER_BOUND=$[${COUNTER_EXAMPLE:15} + 1]
  		    CURRENT_BOUND=$[($UPPER_BOUND + $LOWER_BOUND) / 2]
		    IS_SAFE="N"
		fi	
		echo "$ROUND,$BENCHMARK,$OLD_UPPER_BOUND,$OLD_CURRENT_BOUND,$OLD_LOWER_BOUND,$IS_SAFE,$PRECISION,$ANALYSIS_TIME,$INSTRUCTION_COUNT" >> result.csv
		ROUND=$[$ROUND+1]
		rm -R "$BENCHMARK".tx
		rm output.txt
	done
	echo ",,,,,,,," >> result.csv
done


#( \
#    cd $WCET_DIR ; \
#    make experiment.csv ; \
#)

#export EXPERIMENT_SET="Regexp7 Regexp7_w_bound Regexp8 Regexp8_w_bound RegexpSize9 RegexpSize9_w_bound RegexpSize10 RegexpSize10_w_bound RegexpSize15 RegexpSize15_w_bound"
#export EXPERIMENT_TYPE_SET=".klee1 .tx1"
#export EXPERIMENT_TYPE_SET=".tx1"


#( \
#    cd $WCET_DIR ; \
#    make experiment.csv  ENABLE_COVERAGE=OFF; \
#    make llbmc-experiment.csv ; \
#    mv llbmc-experiment.csv llbmc-experiment.csv1 ; \
#    mv experiment.csv experiment.csv1 ; \
#)


#export EXPERIMENT_SET="statemate statemate_w_bound nsichneu nsichneu_w_bound"

#( \
#    cd $WCET_DIR ; \
#    make experiment.csv  ENABLE_COVERAGE=OFF; \
#    make llbmc-experiment.csv ; \
#    cat llbmc-experiment.csv0 >> llbmc-experiment.csv ; \
#    cat llbmc-experiment.csv1 >> llbmc-experiment.csv ; \
#    cat experiment.csv0 >> experiment.csv ; \
#    cat experiment.csv1 >> experiment.csv ; \
#)


