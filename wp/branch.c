/*
Copyright 2018 National University of Singapore
Execute:  make branch.tx

This example is used as a test program for weakest precondition.
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int wcet, q;
  int a, b, c;

#ifdef LLBMC
  a = __llbmc_nondef_int();
  b = __llbmc_nondef_int();
  c = __llbmc_nondef_int();
  wcet = __llbmc_nondef_int();
#else
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  klee_make_symbolic(&c, sizeof(int), "c");
  klee_make_symbolic(&wcet, sizeof(int), "wcet");
#endif

#ifdef LLBMC
  __llbmc_assume(wcet == 0);
#else
  klee_assume(wcet == 0);
#endif

  q = 5;

  if (a >= 0) {
    wcet += 5;
    q += 3;
  } else {
    wcet += 5;
    q += 4;
  }

  if (b != 1) {
    wcet += 2;
    q += 5;
  } else {
    wcet += 2;
    q += 6;
  }

  if (c >= 0) {
    wcet += 2;
    q += 5;
  } else {
    wcet += 2;
    q += 6;
  }

#ifdef LLBMC
  __llbmc_assert(wcet < 10);
#else
  klee_assert(wcet < 10);
#endif
}
