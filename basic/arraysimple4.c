/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This example triggered an assertion failure in Tracer-X KLEE's
 * Z3Builder::constructActual.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  unsigned char a[4] = "abc";
  unsigned i;
  int p1, p2;

#ifdef LLBMC
  i = __llbmc_nondef_unsigned();
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();

  __llbmc_assume(i < 4);
#else
  klee_make_symbolic(&i, sizeof(i), "i");
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");

  klee_assume(i < 4);
#endif

  if (p1 < 8) {
    if (i > 0)
      a[i] = 'b';
  }

  if (p2 < 8) {
    if (i < 3)
      a[i] = 'a';
  }

#ifdef LLBMC
  __llbmc_assert(a[0] == 'a');
#else
  klee_assert(a[0] == 'a');
#endif

  return 0;
}


