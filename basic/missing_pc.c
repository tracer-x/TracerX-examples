/*
 * This example exhibits the situation where some path conditions that
 * are needed in subsumption check gets missing from the interpolant
 * of the subsumed states. The second issue is that this also shows an
 * over-simplification of formula at subsumption check resulting in
 * successful subsumption that should have failed.
 *
 * Copyright 2017 National University of Singapore
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int wcet,q;
  int a,b,c;
  char p;
  
#ifdef LLBMC
  a = __llbmc_nondef_int();
  b = __llbmc_nondef_int();
  c = __llbmc_nondef_int();
  wcet = __llbmc_nondef_int();
  p = __llbmc_nondef_char();

  if (p) {
    __llbmc_assume(wcet == 1);
  } else {
    __llbmc_assume(wcet == 0);
  }
#else
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  klee_make_symbolic(&c, sizeof(int), "c");
  klee_make_symbolic(&wcet, sizeof(int), "wcet");
  klee_make_symbolic(&p, sizeof(char), "p");
  
  if (p) {
    klee_assume(wcet == 1);
  } else {
    klee_assume(wcet == 0);
  }
#endif
  q = 5;

  if (a >= 0){
    wcet +=5;        // PP 9
     q +=3;
#ifdef LLBMC
     __llbmc_assert(wcet <= 5);
#else
     klee_assert(wcet <= 5);
#endif
  }else{
    wcet+=5;         // PP 2
     q +=4;
  }
  
  if (b != 1){
     wcet+=2;
     q +=5;
  }else{
     wcet+=2;
     q +=6;
  }
  
  if (c >= 0){
     wcet+=2;
     q +=5;
  }else{
     wcet+=2;
     q +=6;
  }

#ifdef LLBMC
  __llbmc_assert(wcet < 10);
#else
  klee_assert(wcet < 10);
#endif
} 
