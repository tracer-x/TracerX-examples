/*
cd
cd NUS/kleeTest
llvm-gcc --emit-llvm -c -g even.c
llvm-gcc -S --emit-llvm even.c
opt -analyze -dot-cfg even.o
klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs even.o
ktest-tool --write-ints klee-last/test000001.ktest
ktest-tool --write-ints klee-last/test000002.ktest
ktest-tool --write-ints klee-last/test000003.ktest

*/
#include <assert.h>

int even(int x) { 

 if( (x % 2) == 0) x = x + 2; 
 else x = x + 1; 
 
 assert(x % 2 == 0);
 return x;
} 

int main() {
  int x;
  klee_make_symbolic(&x, sizeof(x), "x");
  return even(x);
} 

