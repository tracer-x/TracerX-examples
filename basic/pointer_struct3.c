/*
 * Subsumption of dynamically-allocated memory. Although make_node is
 * executed in different paths and should result in different base
 * allocation address, subsumption should still occur as we are using
 * abstract address for comparison.
 *
 * Copyright 2017 National University of Singapore
 */
#include <stdlib.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

struct Node {
  char data;
  struct Node *next;
};

struct Node *make_node(int x) {
  struct Node *n = (struct Node *) malloc(sizeof(struct Node));

  n->data = 32 + x;
  n->next = NULL;

  return n;
}

int main(int argc, char **argv) {
  struct Node *p;
  int p1, p2; // predicates
  int x = 0;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
#endif

  if (p1) {
    p = make_node(1);
  } else {
    p = make_node(2);
  }

  if (p2) {
    x += 1;
  } else {
    x += 2;
  }

  return (int) p->data;
}
