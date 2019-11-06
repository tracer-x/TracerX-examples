echo "Start"


timeout 3600 ./wcet.sh adpcm 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh adpcm 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh bubblesort25 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh bubblesort25 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh cdaudio 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh cdaudio 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh cnt 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh cnt 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh cntShortest 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh cntShortest 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh compress 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh compress 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh diskperf 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh diskperf 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh expint 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh expint 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh floppy 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh floppy 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh floppy2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh floppy2 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh insertsort25 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh insertsort25 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh fly_by_wire 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh fly_by_wire 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh kbfiltr 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh kbfiltr 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh kbfiltr2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh kbfiltr2 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals1 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals1 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals14 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals14 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals15 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals15 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals16 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals16 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals17-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals17-LARGE 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals17-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals17-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals18 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals18 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals19 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals19 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals2 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals20 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals20 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh pals21 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals21 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals22-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals22-LARGE 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals22-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals22-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals23 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals23 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals3 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals3 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals4 50000 
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals4 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals5 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals5 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals6 50000 
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals6 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals7 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals7 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals8 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals8 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh pals9 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh pals9 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh problem10 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh problem10 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh problem11 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh problem11 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh statemate 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh statemate 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh statemate2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh statemate2 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh sumsubset 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh sumsubset 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh tcas 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh tcas 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test1 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test1 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test7 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test7 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh test8 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test8 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh test9 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test9 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh test10 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test10 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test13 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test13 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test14 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test14 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test18-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test18-LARGE 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test18-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test18-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test19-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test19-LARGE 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test19-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test19-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test2 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test2 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test20-LARGE 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test20-LARGE 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test20-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test20-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test21 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test21 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test25 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test25 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test26 50000 
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test26 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test29 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test29 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test3 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test3 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh test30 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test30 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test31 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test31 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test32 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test32 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh test33 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test33 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test34 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test34 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test35 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test35 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test36 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test36 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test37 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test37 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test38 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test38 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test4 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test4 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test45 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test45 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test45-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test45-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test46 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test46 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test46-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test46-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test47 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test47 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test47-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test47-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test49 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test49 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test49-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test49-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test50 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test50 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test50-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test50-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test81 50000 
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test81 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt

timeout 3600 ./wcet.sh test81-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test81-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test82 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test82 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test82-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test82-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test84 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test84 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test84-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test84-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test85 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test85 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test85-SMALL 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test85-SMALL 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test5 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test5 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


timeout 3600 ./wcet.sh test6 50000
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt
timeout 3600 ./wcet.sh test6 50000 -w
rm -R *.tx; rm *.ll; rm *.bc; rm *.c; rm Annotator* clang.tmp annotate.tmp;rm output.txt


echo "Finish"


