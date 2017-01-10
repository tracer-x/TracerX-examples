/*
 * Copyright 2016 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation,
 * Some version failed to report error due to incorrect memory
 * bounds interpolation generated from a subsumed node.
 */

#include <klee/klee.h>
#define N 4

int main(int argc, char **argv)
{
  char s[1000];
  int p1, p2, p3, p4;
  char *p;
  int flag[N];

  klee_make_symbolic(&p1, sizeof(int), "p1");
  klee_make_symbolic(&p2, sizeof(int), "p2");
  klee_make_symbolic(&p3, sizeof(int), "p3");
  klee_make_symbolic(&p4, sizeof(int), "p4");
  klee_make_symbolic(flag, sizeof(int) * N, "flag");

  p = s;

  for (int i = 0; i < N; ++i){
    if (flag[i]) p += i ;
  }

  p += 994;

  // p should be in s
  return *p;
}

