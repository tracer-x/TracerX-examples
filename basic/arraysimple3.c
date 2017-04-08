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
  i = __llbmc_nondef_unsigned();

  __llbmc_assume(i >= 2);
  __llbmc_assume(i <= 3);

  __llbmc_assert(a[i] == 'l');
#else
  klee_make_symbolic(&i, sizeof(i), "i");

  klee_assume(i >= 2);
  klee_assume(i <= 3);

  klee_assert(a[i] == 'l');
#endif

  return 0;
} 


