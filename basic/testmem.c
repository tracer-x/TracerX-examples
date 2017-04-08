/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This example caused assertion failure in Dependency.cpp.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main()
{
  char a[100];
  char b[100];
  char *p = a;
  int x = 0;

#ifdef LLBMC
  p = __llbmc_nondef_uint64_t();
  x = __llbmc_nondef_int();

  __llbmc_assume(x < 50);
  __llbmc_assume(x > 20);
#else
  klee_make_symbolic(&p, sizeof(p), "p");
  klee_make_symbolic(&x, sizeof(x), "x");

  klee_assume(x < 50);
  klee_assume(x > 20);
#endif

  char *n = p[x + 35];

  return 0;  
}
