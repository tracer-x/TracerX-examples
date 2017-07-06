/*
 * Simple example to exhibit a problem previously occurring due the
 * invalid dependency between return value of main (a constant 0) and
 * the constant 0 used in the comparison in the second if
 * conditional. Since the proof was valid, the constant 0 was
 * considered to be part of the interpolant, and hence, the location
 * used to store the constant gets included in the
 * interpolant. Running Tracer-X KLEE with -debug-subsumption=3
 * exhibits this issue. 
 *
 * Copyright 2017 National University of Singapore
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

char _bound[7];
char *wcet;

char tracerx_check(char *p) {
  printf("Timing of Path:%d\n",(int)p-(int)(&(_bound)));
  return *p;
}

int main(int argc, char **argv)
{

  int p1, p2;
  wcet = _bound;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(int), "p1");
  klee_make_symbolic(&p2, sizeof(int), "p2");
#endif
  
  if (p1 > 0) {
    wcet += 1;
    p2 = 1;
  } else {
    wcet += 2;
    p2 = 2;
  }
  if (p2 > 0) {
    wcet += 3;
  } else {
    wcet += 4;
  }

  tracerx_check(wcet);
}

