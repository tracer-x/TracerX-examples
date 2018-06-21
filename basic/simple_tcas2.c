/*
Copyright 2018 National University of Singapore
Execute:  make simple_tcas2.tx

This example represents the over-subsumption bug in TRACER-X (#335).
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int input, output;
int a21;
int a15;
int a12;
int a24;

int main() {
  int kappa = 0;

  klee_make_symbolic(&input, sizeof(int), "input");
  klee_make_symbolic(&a21, sizeof(int), "a21");
  klee_make_symbolic(&a24, sizeof(int), "a24");

  if (a24 == 1 && input == 2 && (a21 == 10 || a21 == 8)) {

  } else if (a24 == 1 && (a21 == 7 || a21 == 8)) {

  } else if (input == 2 && a24 == 1) {
    kappa++;
  }
  klee_assert(kappa < 1);
}
