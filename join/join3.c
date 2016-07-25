/*
 * Simple example to test klee_join.
 *
 * This should result in 0 subsumption as the assignment x = 4 is
 * visited before x = 2 is, and therefore the first visit of klee_join
 * fails to prove that x <= 3.
 *
 * Copyright 2016 National University of Singapore 
 */
#include <klee/klee.h>
#include <assert.h>

int main() {
  int x;
  int cond;

  klee_make_symbolic(&cond, sizeof(cond), "cond");

  if (cond) {
    x = 2;
  } else {
    x = 4;
  }

  klee_join("dummy1", x);

  return x;
} 
