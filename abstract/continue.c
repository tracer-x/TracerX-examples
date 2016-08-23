/*
 * Copyright 2016 National University of Singapore
 *
 * When abstraction fails, we should continue without abstracting.
 */
#include <klee/klee.h>
#include <assert.h>

int main() {
  int x, y;

  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");
  
  if (x) {
    klee_assume(y > 0);
  } else {
    klee_assume(y == 10);
  }

  klee_abstract(y <= 0);

  // Assertion failure should be triggered
  assert(y <= 0);

  return 0;
}
