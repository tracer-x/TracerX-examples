/*
 * Copyright 2016, 2017 National University of Singapore
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  char a[6] = "hello";
  unsigned i;

#ifdef LLBMC
  i = __llbmc_nondef_usigned();

  __llbmc_assume(i <= 1);
#else
  klee_make_symbolic(&i, sizeof(i), "i");

  klee_assume(i <= 1);
#endif

  a[i] = 0;

#ifdef LLBMC
  __llbmc_assert(a[3] != 0);
#else
  klee_assert(a[3] != 0);
#endif

  return 0;
} 


