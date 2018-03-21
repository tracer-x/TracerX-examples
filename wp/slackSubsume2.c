/*
Copyright 2018 National University of Singapore
Execute:  make slackSubsume2.tx

This example is used as a test program for weakest precondition.
The slack computed by the weakest precondition results in subsumption.
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int wcet;
  int a, b;

#ifdef LLBMC
  a = __llbmc_nondef_int();
  b = __llbmc_nondef_int();
#else
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
#endif

  wcet = 0;

  if (a < 0) {
    wcet += 51;
  } else {
    wcet += 50;
  }

  if (b < 0) {
    wcet += 1;
  } else {
    wcet += 2;
  }

  if (a != 1) {
    wcet += 49;
  } else {
    wcet += 50;
  }

#ifdef LLBMC
  __llbmc_assert(wcet < 104);
#else
  klee_assert(wcet < 104);
#endif
}
