/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * Assertion violation should be reported.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

#define N 5

int main() {
  int a[N];
  int i, n, c, d, swap;
  int x = 0, y = 0;

#ifdef LLBMC
  for (unsigned j = 0; j < N; ++j) {
    a[j] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(a, N * sizeof(int), "a");
#endif

  for (i = 0; i < 4; i++) if (a[i]) x++; else y++;

#ifdef LLBMC
  __llbmc_assert(x != 12);
#else
  klee_assert(x != 2);
#endif

  return 0;
}
