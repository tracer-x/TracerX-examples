/*
Copyright 2018 National University of Singapore
Execute:  make slackNoSubsume.tx

This example is used as a test program for weakest precondition.
The slack computed by the weakest precondition does not result
to subsumption.
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int wcet;
int main() {
  int a, b, q;

#ifdef LLBMC
  a = __llbmc_nondef_int();
  b = __llbmc_nondef_int();
#else
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
#endif

  wcet = 0;
  q = 5;

  if (a >= 0) {
    wcet += 5;
    q += 3;
  } else {
    wcet += 2;
    q += 4;
  }

  if (b > 0) {
    wcet += 96;
    q += 5;
  } else {
    wcet += 94;
    q += 6;
  }

#ifdef LLBMC
  __llbmc_assert(wcet <= 100);
#else
  klee_assert(wcet <= 100);
#endif
}
