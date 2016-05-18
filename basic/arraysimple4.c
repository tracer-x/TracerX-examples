/*
 * Copyright 2016 National University of Singapore
 *
 * This example triggered an assertion failure in Tracer-X KLEE's
 * Z3Builder::constructActual.
 */
#include <klee/klee.h>
#include <assert.h>

int main() {
  unsigned char a[4] = "abc";
  unsigned i;
  int p1, p2;

  klee_make_symbolic(&i, sizeof(i), "i");
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");

  klee_assume(i < 4);

  if (p1 < 8) {
    if (i > 0)
      a[i] = 'b';
  }

  if (p2 < 8) {
    if (i < 3)
      a[i] = 'a';
  }

  assert(a[0] == 'a');

  return 0;
}


