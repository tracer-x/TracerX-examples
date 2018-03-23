/*
Copyright 2018 National University of Singapore
Execute:  make test_slack.tx

This example is used as a test program for weakest precondition.
The slack computed by the weakest precondition results in subsumption.
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int p;
  int a, b;

#ifdef LLBMC
  a = __llbmc_nondef_int();
  b = __llbmc_nondef_int();
#else
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
#endif

  p = 0;

  if (a >= 0) {
    p += 10;
  } else {
    p += 20;
  }

  if (b >= 0) {
    p += 30;
  } else {
    p += 40;
  }

#ifdef LLBMC
  __llbmc_assert(p <= 60);
#else
  klee_assert(p <= 60);
#endif
  return 1;
}
