/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation: it
 * should have subsumptions not just at/near the end of the traces.
 * TRACER-X, LLBMC and KLEE can analyze this program.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif



char _bound[31];
char *wcet;

void tracerx_check(char *p) { printf("Timing of Path:%d\n",(int)p-(int)(&(_bound))); *p;}

int main(int argc, char **argv)
{

  int p1, p2, p3, p4, p5;
  wcet = _bound;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  p4 = __llbmc_nondef_int();
  p5 = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(int), "p1");
  klee_make_symbolic(&p2, sizeof(int), "p2");
  klee_make_symbolic(&p3, sizeof(int), "p3");
  klee_make_symbolic(&p4, sizeof(int), "p4");
  klee_make_symbolic(&p5, sizeof(int), "p5");
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

  // wcet should be in _bound
#ifdef LLBMC
    __llbmc_assert(wcet < _bound+100);
#else
  tracerx_check(wcet);
#endif


}

