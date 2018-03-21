/*
Copyright 2018 National University of Singapore
Execute:  make transition2.tx

This example is used as to test the weakest precondition for a transition
using forward intrepreter of KLEE (attempt failed).
*/

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int a[5], b;

#ifdef LLBMC
  a = __llbmc_nondef_int();
  b = __llbmc_nondef_int();
#else
  klee_make_symbolic(&a, 5 * sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
#endif

  a[3] += 5;
  b += 3;
}
