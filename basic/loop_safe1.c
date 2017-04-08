/*
 * Copyright 2016, 2017 National University of Singapore
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif
#include <stdlib.h>

int main()
{
  int N;

#ifdef LLBMC
  N = __llbmc_nondef_int();

  __llbmc_assume(0 <= N);
  __llbmc_assume(N <= 4);
#else
  klee_make_symbolic(&N, sizeof(N), "N");

  klee_assume(0 <= N);
  klee_assume(N <= 4);
#endif

  int x = 0, i = 0;
  while (i < N) {
    if (i % 2 == 0) {
      x += 2;
    }
    i++;
  }

#ifdef LLBMC
  __llbmc_assert(x == N || x == N + 1);
#else
  klee_assert(x == N || x == N + 1); // x == N if N is even, otherwise N is odd
#endif

  return 0;
}
