/*
Copyright 2017 National University of Singapore
Execute:  make absolute.tx

This example indicates that the intersection of the WPExpr
of the left and right branch can be empty.

W1 at true branch: -x >= 0
W2 at false branch: x >= 0

WP before if-stmt: (x < 0 \implies -x >= 0) & (x >= 0 \implies x >= 0) => (ite(x
< 0, W1, W2))

We don't know how to get a conjunction out of this ite().
In fact the ite() is equivalent to TRUE, but we can't infer TRUE.
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int x;

#ifdef LLBMC
  x = __llbmc_nondef_int();
#else
  klee_make_symbolic(&x, sizeof(x), "x");
#endif

  klee_assume(-1 <= x);
  klee_assume(x <= 1);

  if (x < 0)
    x = -x;

#ifdef LLBMC
  __llbmc_assert(x >= 0);
#else
  klee_assert(x >= 0);
#endif
} 
