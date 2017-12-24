/*
 * Copyright 2017 National University of Singapore
 *
 * Trace-X KLEE and KLEE executes only linear in N number of paths,
 * and asymptotically faster compared to LLBMC where LLBMC running time
 * for various N is as follows:
 *
 * N=20: 0.332s
 * N=30: 1.192s
 * N=40: 3.288s
 * N=50: 7.544s
 * N=60: 12.184s
 * N=70: 22.994s
 *
 * Obviously there is an exponential blowup here, without the need to
 * have exponential number of sequences of allocation addresses, as in
 * malloc3.c. Here, one can hypothesize that KLEE and Tracer-X KLEE
 * decide infeasibility of paths early (especially of the if
 * conditional within the for loop), whereas LLBMC delays this
 * decision making to the constraint solving stage, hence it has
 * exponential paths to reason about within the solver.
 *
 * Originally by Roland Yap ryap@comp.nus.edu.sg
 */

#include <stdlib.h>
#include <stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <assert.h>
#include <klee/klee.h>
#endif

#define N 20

int dummy = 1;

int *createvar(int n, int m) {
  int i, *p;

#ifdef LLBMC
  __llbmc_assume(m < n);
#else
  klee_assume(m < n);
#endif

  for (i = 0; i < n; i++) {
    if (i < m)
      p = &dummy;
    else {
      p = (int *)malloc(sizeof(int));
      *p = 0;
    }
  }
  return p;
}

int main() {
  int *v, x;
  int m;
  int n = N;

#ifdef LLBMC
  m = __llbmc_nondef_int();
#else
  klee_make_symbolic(&m, sizeof(m), "m");
#endif

  v = createvar(n, m);
  return *v;
}
