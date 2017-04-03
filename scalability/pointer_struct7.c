/*
 * Simple example to show heap subsumption challenge
 *
 * Copyright 2017 National University of Singapore
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#include <stdlib.h>

#define MAX 9

struct node {
  int val;
  struct node *next;
};

int n; // symbolic

int main(int argc, char **argv) {
  struct node *x, *y;
  int i;

#ifdef LLBMC
  n = __llbmc_nondef_int();
#else
  klee_make_symbolic(&n, sizeof(int), "n");
#endif
  
  x = malloc(sizeof(struct node));
  x->val = n;
  for (i = 1; i < MAX; i++) {
    char nondet;

#ifdef LLBMC
    nondet = __llbmc_nondef_char();
#else
    klee_make_symbolic(&nondet, sizeof(char), "nondet");
#endif
    
    x->next = y = malloc(sizeof(struct node));
    if (nondet)
      y->val = x->val + 10;
    else
      y->val = x->val + 10;
    x = y;
  }

#ifdef LLBMC
  __llbmc_assert(x->val < 999);
#else
  klee_assert(x->val < 999);
#endif
  
  return 0;
}
