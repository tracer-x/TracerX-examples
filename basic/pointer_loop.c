/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation,
 * Some version failed to report error due to incorrect memory
 * bounds interpolation generated from a subsumed node.
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
  int p1, p2, p3, p4;
  char *p;
  int flag[N];

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  p4 = __llbmc_nondef_int();

  for (int i = 0; i < N; ++i) {
    flag[i] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(&p1, sizeof(int), "p1");
  klee_make_symbolic(&p2, sizeof(int), "p2");
  klee_make_symbolic(&p3, sizeof(int), "p3");
  klee_make_symbolic(&p4, sizeof(int), "p4");
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

