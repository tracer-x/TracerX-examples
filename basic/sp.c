/*
 * Copyright 2015, 2017 National University of Singapore
 *
 * cd
 * cd nus/kleetest
 * llvm-gcc --emit-llvm -c -g sp.c
 * llvm-gcc -S --emit-llvm sp.c
 * opt -analyze -dot-cfg sp.o
 * klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs sp.o
 * ktest-tool --write-ints klee-last/test00000?.ktest
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

void proc(int x, int y) {
  int z = 5;

  // These assumes are to prevent underflow
#ifdef LLBMC
  __llbmc_assume(x >= -1);
  __llbmc_assume(y >= -1);
#else
  klee_assume (x >= -1);
  klee_assume (y >= -1);
#endif

  if (x > 0) {
    x = 2;
  } else {
    x += 2;
  }

  if (y > 0) {
    y = 2;
    x++;
  } else {
    y += 2;
    x++;
  }

#ifdef LLBMC
  __llbmc_assert(x + y <= z);
#else
  klee_assert(x + y <= z);
#endif
}

int main() {
  int x, y;

#ifdef LLBMC
  x = __llbmc_nondef_int();
  y = __llbmc_nondef_int();
#else
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");
#endif

  proc(x, y);
  return 0;
} 
