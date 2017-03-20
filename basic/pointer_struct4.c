/*
 * This triggers assertion failure when Tracer-X KLEE is run with
 * -loaded-value-check option. Here the issue is that of the confusion
 * of loaded value since different allocations gets blurred between
 * iterations.
 *
 * Copyright 2017 National University of Singapore
 */
#include <stdlib.h>
#include <klee/klee.h>

struct Node {
  char data;
  struct Node *next;
};

int main(int argc, char **argv) {
  struct Node *p = NULL, *q;
  int p1, p2; // predicates
  int x = 0;

  for (int i = 0; i < 2; ++i) {
    struct Node *new_node =
      (struct Node *) malloc(sizeof(struct Node));

    new_node->data = (char) (2 - i + 96);
    new_node->next = p;
    if (p == NULL)
      q = new_node;
    p = new_node;
  }

  return q->data;
}
