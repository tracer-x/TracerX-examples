/*
 * Simple example to show heap subsumption challenge
 *
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 9

int n; // symbolic input

int main(int argc, char **argv) {
  int *x, *y, z, i;
  x = malloc(sizeof(int));

  klee_make_symbolic(&n, sizeof(int), "n");
  klee_assume(n <= 0);
  
  *x = n; 
  for (i = 1; i < MAX; i++) {
    char nondet;
    
    y = malloc(sizeof(int));

    klee_make_symbolic(&nondet, sizeof(char), "nondet");
    
    if (nondet) {
      z += 1;
      *y = *x + 10;
    } else {
      z += 2;
      *y = *x + 10;
    }
    
    x = y;
  }
  
  klee_assert(*x < n + 999);

  return z;
}
