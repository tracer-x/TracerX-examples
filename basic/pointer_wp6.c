/*
 * Copyright 2017 National University of Singapore
 *
 * With depth-first search (else branch before then branch). There
 * should be subsumptions within subtree A, if slackening actually
 * works. However, there was a bug that the marking due to
 * infeasibility at subtree B is preventing it, resulted in 0
 * subsumptions.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define N 1000

int main() {
  char s[N];
  char *p = s;
  char a, b, c;
  int dummy;
  
#ifdef LLBMC
  a = __llbmc_nondef_char();
  b = __llbmc_nondef_char();
  c = __llbmc_nondef_char();
  for (int i = 0; i < Nx; ++i) {
    s[i] = __llbmc_nondef_char();
  }  
#else
  klee_make_symbolic(&a, sizeof(a), "a");
  klee_make_symbolic(&b, sizeof(b), "b");
  klee_make_symbolic(&c, sizeof(c), "c");
  klee_make_symbolic(s, N * sizeof(char), "s");
#endif

  if (a) {
    /* A */
    if (b) {
      *p++;
    } else {
      *p += 2;
    }
    if (c) {
      *p += 3;
    } else {
      *p += 4;
    }
  } else {
    /* B */
    if (*p) {
      dummy += 1;
    } else {
      dummy += 2;
    }

    if (*p) {
      dummy += 3;
    } else {
      dummy += 4;
    }

    return 0;
  }
  
  return 0;
}
