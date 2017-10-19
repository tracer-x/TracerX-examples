/*
 * Copyright 2017 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation: it
 * should have subsumptions not just at/near the end of the traces.
 * TRACER-X can analyze but LLBMC and KLEE can't analyze this program
 * in 3600 seconds. This program was prepared to test that LLBMC doesn't 
 * have memory bound propagation as is implemented in Tracer-X.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

void tracerx_check(char *p) { *p; } 

char _bound[1651];
char *wcet;

int main(int argc, char **argv)
{
  wcet = _bound;

  int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10;
  char *p;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  p4 = __llbmc_nondef_int();
  p5 = __llbmc_nondef_int();
  p6 = __llbmc_nondef_int();
  p7 = __llbmc_nondef_int();
  p8 = __llbmc_nondef_int();
  p9 = __llbmc_nondef_int();
  p10 = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(int), "p1");
  klee_make_symbolic(&p2, sizeof(int), "p2");
  klee_make_symbolic(&p3, sizeof(int), "p3");
  klee_make_symbolic(&p4, sizeof(int), "p4");
  klee_make_symbolic(&p5, sizeof(int), "p5");
  klee_make_symbolic(&p6, sizeof(int), "p6");
  klee_make_symbolic(&p7, sizeof(int), "p7");
  klee_make_symbolic(&p8, sizeof(int), "p8");
  klee_make_symbolic(&p9, sizeof(int), "p9");
  klee_make_symbolic(&p10, sizeof(int), "p10");
#endif

  if (p1) {
    wcet += 1;
  } else {
    wcet += 2;
  }
  if (p2) {
    wcet += 3;
  } else {
    wcet += 4;
  }
  if (p3) {
    wcet += 5;
  } else {
    wcet += 6;
  }
  if (p4) {
    wcet += 7;
  } else {
    wcet += 8;
  }
  if (p5) {
    wcet += 9;
  } else {
    wcet += 10;
  }
  if (p6) {
    wcet += 11;
  } else {
    wcet += 12;
  }
  if (p7) {
    wcet += 13;
  } else {
    wcet += 14;
  }
  if (p8) {
    wcet += 15;
  } else {
    wcet += 16;
  }
  if (p9) {
    wcet += 17;
  } else {
    wcet += 18;
  }
  if (p10) {
    wcet += 19;
  } else {
    wcet += 20;
  }
  
  // wcet should be in _bound
#ifdef LLBMC
    __llbmc_assert(wcet < _bound+1650);
#else
  tracerx_check(wcet);
#endif
}

