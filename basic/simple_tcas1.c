/*
Copyright 2018 National University of Singapore
Execute:  make simple_tcas2.tx

This example represents the over-subsumption bug in TRACER-X (#333).
It is fixed and this program returns an error.
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int wcet = 0;
  unsigned A, B, C, D, E, F;
  klee_make_symbolic(&A, sizeof(unsigned), "A");
  klee_make_symbolic(&B, sizeof(unsigned), "B");
  klee_make_symbolic(&C, sizeof(unsigned), "C");
  klee_make_symbolic(&D, sizeof(unsigned), "D");
  klee_make_symbolic(&E, sizeof(unsigned), "E");
  klee_make_symbolic(&F, sizeof(unsigned), "F");

  C = 0;

  if (B == 1) {
    F = 0;
  }

  if (A == 0) {
    C = 1;
  }
  if ((C == 1) && ((E == 0) || (D == 0))) {
    if (B == 1) {
      wcet += 1;
    }
  }
  klee_assert(wcet <= 0);
  return 0;
}
