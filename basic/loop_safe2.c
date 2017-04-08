/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This is an example where, as at March 2016, Tracer-X
 * KLEE is slower than KLEE.
 */
#include <stdlib.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <assert.h>
#include <klee/klee.h>
#endif

int main(){
   int i;
   int j;

#ifdef LLBMC
  i = __llbmc_nondef_int();
  j = __llbmc_nondef_int();

  __llbmc_assume(0 <= i);
  __llbmc_assume(i <= 10);
#else
  klee_make_symbolic(&i, sizeof(i), "i");
  klee_make_symbolic(&j, sizeof(j), "j");

  klee_assume(0 <= i);
  klee_assume(i <= 10);
#endif

   int x,y;
   x=i;
   y=j;

   while (x!=0) {
      x--;
      y--;
   }

   if (i==j) {
#ifdef LLBMC
    __llbmc_assert(y == 0);
#else
    klee_assert(y == 0);
#endif
   }
   
   return 1;
}
