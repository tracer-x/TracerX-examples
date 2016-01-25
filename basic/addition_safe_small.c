/*
Copyright 2015 National University of Singapore 
cd
cd nus/kleetest
llvm-gcc --emit-llvm -c -g addition_safe_small.c
llvm-gcc -S --emit-llvm addition_safe_small.c
opt -analyze -dot-cfg addition_safe_small.o
klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs addition_safe_small.o
ktest-tool --write-ints klee-last/test000001.ktest
ktest-tool --write-ints klee-last/test000002.ktest
ktest-tool --write-ints klee-last/test000003.ktest

*/
#include <klee/klee.h>
#include <assert.h>

int y;

int add(int p1, int x) { 
if(x <= 0){
	 if(p1 > 8) x = x;
	 	else {x = x + 2;}

	 assert(x <= 6);
 }
 return x;
} 
int main() {
  int p1;
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&y, sizeof(y), "y");
  return add(p1, y);
} 
