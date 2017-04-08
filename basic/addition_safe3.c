/*
Copyright 2015, 2017 National University of Singapore

Smaller version of addition_safe1.c

cd
cd nus/kleetest
llvm-gcc --emit-llvm -c -g addition_safe3.c
llvm-gcc -S --emit-llvm addition_safe3.c
opt -analyze -dot-cfg addition_safe3.o
klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs addition_safe3.o
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

int y;

int add(int p1, int x) {
#ifdef LLBMC
  __llbmc_assume(x <= 0);
#else
  klee_assume(x <= 0);
#endif

  if (p1 > 8)
    x = x;
  else
    x = x + 2;

#ifdef LLBMC
  __llbmc_assert(x <= 6);
#else
  klee_assert(x <= 6);
#endif

  return x;
}

int main() {
  int p1;
#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  y = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&y, sizeof(y), "y");
#endif
  return add(p1, y);
}
