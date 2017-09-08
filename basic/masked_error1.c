/*
 * Copyright 2017 National University of Singapore
 *
 * With depth-first strategy, this shows an example where the first
 * memory bound error at A masks the assertion violation at B. As the
 * result Tracer-X could not find the assertion violation, yet KLEE
 * could find it. This is because the interpolant is TRUE at error
 * point, such that this interpolant subsumes the path that would lead
 * to error.
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
  e = *d;
  
  if (flag)
    /* B */
    assert(0);
  
  return 0;
}
