/*
 * Copyright 2016 National University of Singapore
 *
 * For this example we need to ensure that the formula
 * constructed for subsumption check is correct. In some
 * versions of Tracer-X, the global version of int x
 * is considered a composite allocation.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int x;

int main() {
  int p1, p2, p3;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  x = __llbmc_nondef_int();

  __llbmc_assume(x <= 0);
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&x, sizeof(x), "x");

  klee_assume (x <= 0);
#endif

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

#ifdef LLBMC
  __llbmc_assert(x <= 6);
#else
  klee_assert(x <= 6);
#endif

  return 0;
}
