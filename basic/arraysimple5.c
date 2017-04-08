/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * Subsumption test with symbolic index. This exposed some supposedly
 * bounded variables appearing unbounded in subsumption check.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  unsigned char a[5] = "aabb";
  unsigned i, j;
  int p1, p2, p3;

#ifdef LLBMC
  i = __llbmc_nondef_unsigned();
  j = __llbmc_nondef_unsigned();
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();

  __llbmc_assume(i < 4);
  __llbmc_assume(j < 4);
#else
  klee_make_symbolic(&i, sizeof(i), "i");
  klee_make_symbolic(&j, sizeof(j), "j");  
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");

  klee_assume(i < 4);
  klee_assume(j < 4);
#endif

  if (p1 < 8) {
    a[i] = 'a';
  } else {
    if (j > 2)
      a[j] = 'b';
  }

  if (p2 < 8) {
    if (i > 2)
      a[i] = 'a';
  } else {
    if (j > 2)
      a[j] = 'c';
  }

  if (p3 < 8) {
    if (i > 1)
      a[i] = 'c';
  } else {
    if (j < 2)
      a[j] = 'a';
  }

  if (i < 2) {
#ifdef LLBMC
    __llbmc_assert(a[i] == 'a');
#else
    klee_assert(a[i] == 'a');
#endif
  }

  return 0;
}


