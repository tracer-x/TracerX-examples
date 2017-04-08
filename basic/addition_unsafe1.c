/*
Copyright 2015, 2016 National University of Singapore

Assertion can be violated here.

cd
cd nus/kleetest
llvm-gcc --emit-llvm -c -g addition.c
llvm-gcc -S --emit-llvm addition.c
opt -analyze -dot-cfg addition.o
klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs addition.o
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

int add(int p1, int p2, int p3, int x) {
#ifdef LLBMC
  __llbmc_assume(x <= 0);
#else
  klee_assume (x <= 0);
#endif

  if (p1 > 8)
    x = x + 1; 
  if (p2 > 8)
    x = x;
  else
    x = x + 2;
  if (p3 > 8)
    x = x + 3;

#ifdef LLBMC
  __llbmc_assume(x <= 5);
#else
  klee_assert(x <= 5);
#endif

  return x;
} 

int main() {
  int p1, p2, p3, x;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  x = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&x, sizeof(x), "x");
#endif

  return add(p1, p2, p3, x);
} 
