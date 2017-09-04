/*
 * Copyright 2017 National University of Singapore
 *
 * In some versions of Tracer-X, running on this example results in
 * over-subsumption, with depth-first search.
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  char c, d, e;
  int flag = 0;
  int x = 0;
  
#ifdef LLBMC
  d = __llbmc_nondef_char();
  e = __llbmc_nondef_char();
#else
  klee_make_symbolic(&d, sizeof(d), "d");
  klee_make_symbolic(&e, sizeof(e), "e");
#endif

  if (d) {
    c = 'B';
  } else {
    c = 'A';
  }

  if (e) {
    x++;
  } else {
    x+=2;
  }

  switch (c) {
  case 'A': {
    x++;
    break;
  }
  case 'B': {
    flag = 1;
    break;
  }
  default:
    break;
  }
  
  if (flag)
    assert(0);

  return x;
} 
