/*
Copyright 2017 National University of Singapore
Execute:  make absolute.tx

This example compares KLEE, TRACER-X + Deletion and
TRACER-X + WP.

The following is the result for TRACER-X + WP in less than 1 seconds:

KLEE: done:     subsumed paths = 295
KLEE: done:     error paths = 1
KLEE: done:     program exit paths = 2

TRACER-X + deletion would be able to do it in 30 seconds:

KLEE: done:     subsumed paths = 9702
KLEE: done:     error paths = 1
KLEE: done:     program exit paths = 199

Klee definitely has to go through 2^100 paths to find the expected sequence.
*/

#include <klee/klee.h>

int main() {
  int y, j = 0;

  klee_make_symbolic(&y, sizeof(y), "y");

  int i = 0;
  for (; i < 100; i++) {
    int x;
    klee_make_symbolic(&x, sizeof(x), "x");
    if (x > 0)
      j++;
  }
  printf("%d\n", j);
  if (j >= 100)
    klee_assert(0);

  return 0;
}
