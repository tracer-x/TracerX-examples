clang -c -S -emit-llvm -g $1.c &> clang.tmp
#g++ -o Annotator Annotator.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl &> annotate.tmp
./Annotator $1.ll 1> $1-trans.ll
llvm-as $1-trans.ll -o $1.bc
 
