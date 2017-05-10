/*
 * Simple example to show heap subsumption challenge. Here, malloc()
 * is called within the then and else bodies of if conditional.
 * For this example, LLBMC seems to get exponentially slower as MAX
 * is increased.
 *
 * Copyright 2017 National University of Singapore
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif
#include <stdlib.h>

#define MAX 9

int main(int argc, char **argv) {
  int *x, *y, i, z = 0;
  int n;
  
#ifdef LLBMC
  n = __llbmc_nondef_int();
  __llbmc_assume(n < 10);
#else
  klee_make_symbolic(&n, sizeof(n), "n");
  klee_assume(n < 10);
#endif

  x = (int *) malloc(sizeof(int));
  *x = n; // symbolic input
  for (i = 1; i < MAX; i++) {
    char c;
#ifdef LLBMC
    c = __llbmc_nondef_char();
#else
    klee_make_symbolic(&c, sizeof(c), "c");
#endif
    if (c) {
      y = (int *) malloc(sizeof(int));
      *y = *x + 10; z = z + 1;
    } else {
      y = (int *) malloc(sizeof(int));
      *y = *x + 10;
    }
    x = y;
  }

#ifdef LLBMC
  __llbmc_assert(*x < n + 999);
#else
  klee_assert(*x < n + 999);
#endif
}
