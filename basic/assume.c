/*
 * Copyright 2017 National University of Singapore 
 *
 * This example showed missed subsumption due to the error in the
 * construction of existentially-quantified formula for Z3.
 */

#include <klee/klee.h>
#include <assert.h>

int inc(int x) { 
  return x + 1;
} 

int main() {
  char p1, p2;
  int x;
  
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");

  /* We gain subsumption when this is replaced with an assignment of x
     with 0. */
  klee_assume(x == 0);
  
  if (p1) {
    x++;
  } else {
    x = inc(x);
  }

  if (p2) {
    x++;
  } else {
    x = inc(x);
  }

  klee_assert(x > 0);
  
  return 0;
} 
