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

int UB = 4000;
int B = 4000;
int LB = 1;
int wcet;

int main() {

  int a, b,c;
  wcet = 0;
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  klee_make_symbolic(&c, sizeof(int), "c");

  //klee_assume(!(b>0 && c<=0));
  //klee_assume(!(a<=0 && b<=0 && c<=0));

  if (a <= 0) {
    wcet += 150;    
  } else {
    wcet += 50;
  }
  if (b > 0) {
    wcet += 201;
  } else {
    wcet += 100;
  }
  if (a == 1) {
    wcet += 300;
  } else {
    wcet += 250;
  }

  printf("Timing of Path:%d\n",wcet); 
  klee_assert(wcet <= B);
}
