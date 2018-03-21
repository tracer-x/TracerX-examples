/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation: it
 * should have interpolations not just at/near the end of the traces.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

void tracerx_check(char *p) { *p; } 

char _bound[20];
int w_max = 5;
char *wcet;
int w;

int main(int argc, char **argv)
{

  int p1, p2, p3, p4, p5;
  wcet = _bound;
  w = 0;

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

  if (p1 && w <= w_max) {
    wcet += 1;
    w += 10;
  } 
  if (p2 && w <= w_max) {
    wcet += 3;
    w += 8;
  } 
  if (p3 && w <= w_max) {
    wcet += 5;
    w += 6;
  } 
  if (p4 && w <= w_max) {
    wcet += 7;
    w += 4;
  } 
  if (p5 && w <= w_max) {
    wcet += 9;
    w += 2;
  } 

  // wcet should be in _bound
#ifdef LLBMC
    __llbmc_assert(wcet < _bound+100);
#else
  tracerx_check(wcet);
#endif


}

