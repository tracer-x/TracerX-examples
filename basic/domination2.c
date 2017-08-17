/*
 * Copyright 2017 National University of Singapore
 *
 * This example demonstrates another saving of tree traversals due to
 * memory domination computation. With depth-first search, the else
 * branch of the first if conditional with y >= 0 as the condition (A), is
 * traversed first. This results in the retaining of the constraint y
 * < 0 for the subtree of the else branch due to a false branch in the
 * second if conditional with y >= 0 as the condition (B).
 *
 * Without memory domination, subsumptions between the subtrees of the
 * two visittations of (C) would not be possible.
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  char p1, p2, p3, p4, x = 0, y;

#ifdef LLBMC
  p1 = __llbmc_nondef_char();
  p2 = __llbmc_nondef_char();
  p3 = __llbmc_nondef_char();
  p4 = __llbmc_nondef_char();
  y = __llbmc_nondef_char();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&p4, sizeof(p4), "p4");
  klee_make_symbolic(&y, sizeof(y), "y");
#endif

  /* A */
  if (y >= 0) {
    x = x + 1;
  } else {
    if (p1 > 8) {
      x = x + 1;
    } else {
      return 0;
    }
    if (p2 > 8) {
      x = x + 1;
      /* B */
      if (y >= 0) {
        return 1;
      }
      return 0;
    } else {
      x = x + 2;
    }
  }

  /* C */
  if (p3 > 8) {
    x = x + 1;
  } else {
    x = x + 2;
  }

  if (p4 > 8) {
    x = x + 1;
  } else {
    x = x + 2;
  }

  return x;
}
