/*
 * Simple example to show heap subsumption challenge
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

int n; // symbolic input

int main(int argc, char **argv) {
  int *x, *y, z = 0, i;
  x = malloc(sizeof(int));

#ifdef LLBMC
  n = __llbmc_nondef_int();
  __llbmc_assume(n <= 0);
#else
  klee_make_symbolic(&n, sizeof(int), "n");
  klee_assume(n <= 0);
#endif

  *x = n; 
  for (i = 1; i < MAX; i++) {
    char nondet;
    
    y = malloc(sizeof(int));

#ifdef LLBMC
    nondet = __llbmc_nondef_char();
#else
    klee_make_symbolic(&nondet, sizeof(char), "nondet");
#endif

    if (nondet) {
      z += 1;
      *y = *x + 10;
    } else {
      z += 2;
      *y = *x + 10;
    }
    
    x = y;
  }

#ifdef LLBMC
  __llbmc_assert(*x < n + 999);
#else
  klee_assert(*x < n + 999);
#endif

  return z;
}
