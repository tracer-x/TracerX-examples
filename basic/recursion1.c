/*
 * This example demonstrates an issue that intermediate local
 * allocations that are forward dominated by subsequent allocations
 * are still considered in subsumption checks. In the function foo,
 * the intermediate locals y of different symbolic execution paths
 * should be matched, although they have different callsite history.
 *
 * Copyright 2017 National University of Singapore
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

#define MAX 5

int i = 0;

int foo(int *x) {
  char c;
  int y, z = 0;

  if (++i >= MAX)
    return *x;

#ifdef LLBMC
  c = __llbmc_nondef_char();
#else
  klee_make_symbolic(&c, sizeof(c), "c");
#endif
  if (c) {
    y = *x + 10;
    z = z + 1;
    return foo(&y);
  }

  y = *x + 10;
  return foo(&y);
}

int main(int argc, char **argv) {
  int n;

#ifdef LLBMC
  n = __llbmc_nondef_char();
  __llbmc_assume(n < 10);
#else
  klee_make_symbolic(&n, sizeof(n), "n");
  klee_assume(n < 10);
#endif

  int x = n;
  int result = foo(&x);

  i = 0;

#ifdef LLBMC
  __llbmc_assert(result < n + 999);
#else
  klee_assert(result < n + 999);
#endif
  return 0;
}
