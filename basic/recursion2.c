/*
 * This example demonstrates memory bound interpolation (slackening)'s
 * effectiveness. Exponential blowup in the number of paths is
 * observed without it.
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

#define MAX 15

int i = 0;
int a[1000];

int main(int argc, char **argv) {
  int *x;
  int *y, n;

#ifdef LLBMC
  n = __llbmc_nondef_int();
#else
  klee_make_symbolic(&n, sizeof(n), "n");
#endif

  x = malloc(sizeof(int));
  *x = 0;
  for (i = 0; i < MAX; ++i) {
    char c;
#ifdef LLBMC
    c = __llbmc_nondef_char();
#else
    klee_make_symbolic(&c, sizeof(c), "c");
#endif
    if (c) {
      y = malloc(sizeof(int));
      *y = *x + 10;
    } else {
      y = malloc(sizeof(int));
      *y = *x + 15;
    }
    x = y;
  }

  int offset = (*x);

  return *(a + offset);
}
