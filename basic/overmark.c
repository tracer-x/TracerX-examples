/*
 * Copyright 2017 National University of Singapore
 *
 * This example demonstrates an over-marking of path condition in a
 * version of Tracer-X KLEE, with depth-first search strategy.
 *
 * Below, the assert at (C) is dependent on the assume at (B), and the
 * assert at (D) is dependent on the assume at (A). In a version, (B)
 * causes non-subsumption of (D) by its previous visitation, as the
 * previous visitation unnecessarily inherits (B) in its interpolant.
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  char p1, p2, p3, y;
  int x = 0;
  
#ifdef LLBMC
  p1 = __llbmc_nondef_char();
  p2 = __llbmc_nondef_char();
  p3 = __llbmc_nondef_char();
  y = __llbmc_nondef_char();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&y, sizeof(y), "y");
#endif

  /* A */
#ifdef LLBMC
  __llbmc_assume(y < 4);
#else
  klee_assume(y < 4);
#endif
  
  if (p1 < 8) {
    x++;
  } else {
    /* B */
#ifdef LLBMC
    __llbmc_assume(y > 1);
#else
    klee_assume(y > 1);
#endif
    
    if (p2 < 8) {
      x++;
    } else {
      /* C */
#ifdef LLBMC
      __llbmc_assert(y > 0);
#else
      klee_assert(y > 0);
#endif
      return 0;
    }
  }

  if (p3 < 8) {
    /* D */
#ifdef LLBMC
    __llbmc_assert(y < 5);
#else
    klee_assert(y < 5);
#endif
  } else {
    x++;
  }
  
  return x;
}

