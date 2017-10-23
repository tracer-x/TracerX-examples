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

  int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20;
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
  p11 = __llbmc_nondef_int();
  p12 = __llbmc_nondef_int();
  p13 = __llbmc_nondef_int();
  p14 = __llbmc_nondef_int();
  p15 = __llbmc_nondef_int();
  p16 = __llbmc_nondef_int();
  p17 = __llbmc_nondef_int();
  p18 = __llbmc_nondef_int();
  p19 = __llbmc_nondef_int();
  p20 = __llbmc_nondef_int();
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
  klee_make_symbolic(&p11, sizeof(int), "p11");
  klee_make_symbolic(&p12, sizeof(int), "p12");
  klee_make_symbolic(&p13, sizeof(int), "p13");
  klee_make_symbolic(&p14, sizeof(int), "p14");
  klee_make_symbolic(&p15, sizeof(int), "p15");
  klee_make_symbolic(&p16, sizeof(int), "p16");
  klee_make_symbolic(&p17, sizeof(int), "p17");
  klee_make_symbolic(&p18, sizeof(int), "p18");
  klee_make_symbolic(&p19, sizeof(int), "p19");
  klee_make_symbolic(&p20, sizeof(int), "p20");
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
  if (p11) {
    wcet += 21;
  } else {
    wcet += 22;
  }
  if (p12) {
    wcet += 23;
  } else {
    wcet += 24;
  }
  if (p13) {
    wcet += 25;
  } else {
    wcet += 26;
  }
  if (p14) {
    wcet += 27;
  } else {
    wcet += 28;
  }
  if (p15) {
    wcet += 29;
  } else {
    wcet += 30;
  }
  if (p16) {
    wcet += 31;
  } else {
    wcet += 32;
  }
  if (p17) {
    wcet += 33;
  } else {
    wcet += 34;
  }
  if (p18) {
    wcet += 35;
  } else {
    wcet += 36;
  }
  if (p19) {
    wcet += 37;
  } else {
    wcet += 38;
  }
  if (p20) {
    wcet += 39;
  } else {
    wcet += 40;
  }

  // wcet should be in _bound
#ifdef LLBMC
    __llbmc_assert(wcet < _bound+1650);
#else
  tracerx_check(wcet);
#endif


}

