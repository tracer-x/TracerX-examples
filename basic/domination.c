/*
 * An example to test new memory region domination, where dominated
 * memory addresses is removed from consideration in subsumption
 * checks.
 *
 * Copyright 2017 National University of Singapore
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  char p1, p2, p3;
  char n, x, y, z, u;

#ifdef LLBMC
  p1 = __llbmc_nondef_char();
  p2 = __llbmc_nondef_char();
  p3 = __llbmc_nondef_char();
  n = __llbmc_nondef_char();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&n, sizeof(n), "n");
#endif

#ifdef LLBMC
  __llbmc_assume(n <= 0);
#else
  klee_assume(n <= 0);
#endif
  x = n;

  if (p1 > 8)
    y = x + 1;
  else
    y = x + 2;

  if (p2 > 8)
    z = y + 1;
  else
    z = y + 2;

  if (p3 > 8)
    u = z + 1;
  else
    u = z + 2;

#ifdef LLBMC
  __llbmc_assert(u <= n + 6);
#else
  klee_assert(u <= n + 6);
#endif

  return 0;
}
