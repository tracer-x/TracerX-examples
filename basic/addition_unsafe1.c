/*
 * Copyright 2015-2017 National University of Singapore
 *
 * Assertion can be violated here.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int add(char p1, char p2, char p3, int x) {
#ifdef LLBMC
  __llbmc_assume(x <= 0);
#else
  klee_assume(x <= 0);
#endif

  if (p1 > 8)
    x = x + 1; 
  if (p2 > 8)
    x = x;
  else
    x = x + 2;
  if (p3 > 8)
    x = x + 3;

#ifdef LLBMC
  __llbmc_assume(x <= 5);
#else
  klee_assert(x <= 5);
#endif

  return x;
} 

int main() {
  char p1, p2, p3;
  int x;

#ifdef LLBMC
  p1 = __llbmc_nondef_char();
  p2 = __llbmc_nondef_char();
  p3 = __llbmc_nondef_char();
  x = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&x, sizeof(x), "x");
#endif

  return add(p1, p2, p3, x);
} 
