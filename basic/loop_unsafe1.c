/*
 * Copyright 2016 National University of Singapore
 *
 * Assertion violation should be reported.
 */
#include <klee/klee.h>
#include <assert.h>

#define N 5

int main() {
  int a[N];
  int i, n, c, d, swap;
  int x = 0, y = 0;

  klee_make_symbolic(a, N * sizeof(int), "a");

  for (i = 0; i < 4; i++) if (a[i]) x++; else y++;

  assert(x != 2);
}
