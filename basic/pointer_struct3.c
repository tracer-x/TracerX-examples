/*
 * Subsumption of dynamically-allocated memory.
 *
 * Copyright 2017 National University of Singapore
 */
#include <stdlib.h>
#include <klee/klee.h>

struct Node {
  char data;
  struct Node *next;
};

struct Node *make_node() {
  struct Node *n = (struct Node *) malloc(sizeof(struct Node));

  n->data = 32;
  n->next = NULL;

  return n;
}

int main(int argc, char **argv) {
  struct Node *p;
  int p1, p2; // predicates
  int x = 0;

  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  
  if (p1) {
    p = make_node();
  } else {
    p = make_node();
  }

  if (p2) {
    x += 1;
  } else {
    x += 2;
  }

  if (p->data == 32)
    return 0;
  
  return 1;
}
