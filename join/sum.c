/*
 * Copyright 2016 National University of Singapore
 */
#include <klee/klee.h>
#include <assert.h>
#include <stdio.h>

#define SIZE 3

int main() {
  char a[SIZE];
  unsigned i, sum1 = 0, sum2 = 0;

  klee_make_symbolic(a, SIZE * sizeof(char), "a");

  for (i = 0; i < SIZE; ++i) {
    if (a[i] > 0) sum1 += a[i];
  }

  for (i = 0; i < SIZE; ++i) {
    sum2 += a[i];
    klee_join("sum", a, i, sum2);
  }

  assert(sum1 == sum2); // The assertion should be violated because sum1 only sum positive numbers, while sum2 sum all the numbers.
  return 0;
}
