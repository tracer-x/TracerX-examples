/*
 * Simple example to test klee_join.
 *
 * This should result in 1 subsumption as both branches proves
 * dummy1(x) :- x <= 3.
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
    x = 3;
  }

  klee_join("dummy1", x);

  return x;
} 
