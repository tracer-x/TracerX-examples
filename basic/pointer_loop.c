/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation.
 * Some versions failed to report error due to incorrect memory bounds
 * interpolation generated from a subsumed node.
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define N 4

int main(int argc, char **argv)
{
  char s[1000];
  char *p;
  int flag[N];

#ifdef LLBMC
  for (int i = 0; i < N; ++i) {
    flag[i] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(flag, sizeof(int) * N, "flag");
#endif

  p = s;

  for (int i = 0; i < N; ++i){
    if (flag[i]) p += i ;
  }

  p += 994;

  // p should be in s
  return *p;
}

