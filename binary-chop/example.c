/*
Copyright 2018 National University of Singapore
Execute:  make slackSubsume.tx

This example is used as a test program for weakest precondition.
The slack computed by the weakest precondition results in subsumption.
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int UB = 1000;
int B = 1000;
int LB = 1;
int wcet;

int main() {

  int q;
  int a, b;
  wcet = 0;
#ifdef LLBMC
  a = __llbmc_nondef_int();
  b = __llbmc_nondef_int();
#else
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
#endif

  q = 5;
  if (a < 0) {
    wcet += 150;
    q += 3;
  } else {
    wcet += 100;
    q += 4;
  }
  if (b < 0) {
    wcet += 201;
    q += 5;
  } else {
    wcet += 100;
    q += 6;
  }
  if (b == 1) {
    wcet += 200;
    q += 5;
  } else {
    wcet += 100;
    q += 6;
  }
  printf("Timing of Path:%d\n",wcet); 
#ifdef LLBMC
  __llbmc_assert(wcet <= B);
#else
  klee_assert(wcet <= B);
#endif
}
