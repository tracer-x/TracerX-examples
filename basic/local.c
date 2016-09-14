/*
 * Copyright 2016 National University of Singapore
 *
 * This example exhibits the issue that the container of local
 * pointers are marked to be in the interpolant, and since the
 * container has absolute address between invocation instances of the
 * same function, subsumption fails as the addresses differ.
 */
#include <klee/klee.h>
#include <assert.h>
#include <stdlib.h>

int add2(int p3, int x) {
  int *c = malloc(sizeof(int));

  *c = x;

  if (p3 > 8)
    x = *c + 1;
  else
    x = *c + 2;

  free(c);
  return x;
}

int add1(int p2, int p3, int x) {
  int *c = malloc(sizeof(int));

  *c = x;

  if (p2 > 8)
    x = *c + 1;
  else
    x = *c + 2;

  free(c);
  return add2(p3, x);
}

int add(int p1, int p2, int p3, int x) {
  int *c = malloc(sizeof(int));

  *c = x;

  if (p1 > 8)
    x = *c + 1;
  else
    x = *c + 2;

  free(c);
  return add1(p2, p3, x);
}

int main() {
  int p1, p2, p3, x;
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&x, sizeof(x), "x");

  klee_assume(x <= 0);

  x = add(p1, p2, p3, x);

  assert(x <= 6);

  return x;
}
