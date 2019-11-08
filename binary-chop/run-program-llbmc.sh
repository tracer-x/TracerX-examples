echo "Start"


timeout 3600 ./wcet-llbmc.sh adpcm 200000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh bubblesort25 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh cdaudio 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh cnt 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh cntShortest 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh compress 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh diskperf 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh expint 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh floppy 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh floppy2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh insertsort25 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh fly_by_wire 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh kbfiltr 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh kbfiltr2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals1 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals14 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals15 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals16 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals17-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals17-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals18 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals19 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals20 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals21 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals22-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals22-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals23 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals3 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals4 50000 
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals5 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals6 50000 
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals7 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals8 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh pals9 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh problem10 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh problem11 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh statemate 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh statemate2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh sumsubset 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh tcas 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test1 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test7 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test8 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test9 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test10 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test13 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test14 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test18-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test18-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test19-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test19-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test20-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test20-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test21 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test25 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test26 50000 
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test29 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test3 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test30 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test31 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test32 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test33 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test34 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test35 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test36 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test37 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test38 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test4 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test45 200000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test45-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test46 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test46-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test47 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test47-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test49 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test49-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test50 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test50-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test81 50000 
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test81-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test82 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test82-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test84 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test84-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test85 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test85-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test5 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet-llbmc.sh test6 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

echo "Finish"


