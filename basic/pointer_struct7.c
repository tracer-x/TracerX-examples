/*
 * Simple example to show heap subsumption challenge
 *
 * Copyright 2017 National University of Singapore
 */

#include <klee/klee.h>
#include <assert.h>
#include <stdlib.h>

#define MAX 9

struct node {
  int val;
  struct node *next;
};

int n; // symbolic

int main(int argc, char **argv) {
  struct node *x, *y;
  int z, i;

  klee_make_symbolic(&n, sizeof(int), "n");
  klee_assume(n <= 0);
 
  x = malloc(sizeof(struct node));
  x->val = n;
  for (i = 1; i < MAX; i++) {
    char nondet;

    klee_make_symbolic(&nondet, sizeof(char), "nondet");

    x->next = y = malloc(sizeof(struct node));
    if (nondet) {
      z += 1;
      y->val = x->val + 10;
    } else {
      z += 2;
      y->val = x->val + 10;
    }
    
    x = y;
  }

  klee_assert(x->val < n + 999);

  return z;
}