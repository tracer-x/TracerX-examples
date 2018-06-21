/*
Copyright 2018 National University of Singapore
Execute:  make partition2.tx

This example is used as a test program for weakest precondition.
In this example, a weakest precondition is generated from both
the target (klee_assert) and infeasible paths. The important point
is that two partitions share variable 'a' in the WP formula.
As a result, the intersection of the WP formulas should be done
while considering this point.
*/


#include <klee/klee.h>

int main() {
  int wcet;
  int a, b;


  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");

  klee_assume(a <= 10);

  wcet = 0;

  if (a >= 0) {
    wcet += 5;
  } else {
    wcet += 6;
  }

  if (a != 1) {
    wcet += 4;
  } else {
    wcet += 5;
  }


  klee_assert(wcet <= 11 && a <= 10);
}
