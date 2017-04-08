/*
Copyright 2015, 2017 National University of Singapore 
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
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int even(int x) { 
 if((x % 2) == 0)
   x = x + 2;
 
 else x = x + 1; 

#ifdef LLBMC
 __llbmc_assert(x % 2 == 0);
#else
 klee_assert(x % 2 == 0);
#endif
 
 return x;
} 

int main() {
  int x;

#ifdef LLBMC
  x = __llbmc_nondef_int();
#else
  klee_make_symbolic(&x, sizeof(x), "x");
#endif
  
  return even(x);
} 

