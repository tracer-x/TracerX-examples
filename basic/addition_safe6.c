/*
 * Copyright 2016 National University of Singapore
 *
 * For this example we need to ensure that the formula
 * constructed for subsumption check is correct. In some
 * versions of Tracer-X, the global version of int x
 * is considered a composite allocation.
 */
#include <klee/klee.h>
#include <assert.h>

int x;

int main() {
  int p1, p2, p3;
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&x, sizeof(x), "x");

  klee_assume (x <= 0);

  if (p1 > 8)
    x = x + 1;
  else
    x = x + 2;
  if (p2 > 8)
    x = x + 1;
  else
    x = x + 2;
  if (p3 > 8)
    x = x + 1;
  else
    x = x + 2;
  
  assert(x <= 6);

  return 0;
}
