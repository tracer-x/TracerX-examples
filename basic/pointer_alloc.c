/*
 * Examples of subsumptions between pointers of different
 * allocations. This example should be run with depth-first strategy.
 * It triggered an assertion failure in Tracer-X.
 *
 * With depth-first strategy, KLEE would traverse the else branches
 * first, resulting in the assignment of big_mem to p first, which
 * makes pointer access at the end of the program safe. When the then
 * branch of the first conditional is traversed, p is assigned to
 * smaller memory where the pointer access at the end of the program
 * is incorrect. In this case, this other path should not be subsumed.
 *
 * Copyright 2017 National University of Singapore
 */
#include <klee/klee.h>

#define SMALL_MEM_SIZE 100
#define BIG_MEM_SIZE (SMALL_MEM_SIZE * 2)

int main(int argc, char **argv) {
  char *p;
  int p1, p2; // predicates
  char small_mem[100], big_mem[200];
  int x = 0;
  
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");

  if (p1) {
    p = small_mem;
  } else {
    p = big_mem;
  }

  p += SMALL_MEM_SIZE;

  if (p2) {
    x += 1;
  } else {
    x += 2;
  }

  return ((int) *p) + x;
}

