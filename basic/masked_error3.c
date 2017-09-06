/*
 * Copyright 2017 National University of Singapore
 *
 * With depth-first strategy, this shows an example where the first
 * assertion violation at A masks potentially masks the assertion
 * violation at B. Tracer-X KLEE handles this case correctly and
 * reporting both assertion violations. This is because an assert() is
 * a branch, and branch feasibility/infeasibility are correctly
 * handled by the implemented interpolation mechanism.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  char str[3];
  char c, *d = str, e, f;
  int flag = 0, dummy = 0;

  klee_make_symbolic(&c, sizeof(c), "c");
  klee_make_symbolic(&f, sizeof(f), "f");

  if (c) {
    d += 1;
    flag = 1;
  } else {
    d += 5;
  }

  if (f) {
    dummy += 2;
  } else {
    dummy++;
  }

  /* A */
  assert(flag > 0);
  
  if (flag)
    /* B */
    assert(0);
  
  return 0;
}
