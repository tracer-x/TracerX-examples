/*
 * Copyright 2016 National University of Singapore
 *
 * Author: Joxan Jaffar
 */
#include <klee/klee.h>
#include <assert.h>

#define SIZE 5

int main() {
  char a[SIZE];
  unsigned i, count1 = 0, count2 = 0;

  klee_make_symbolic(a, SIZE * sizeof(char), "a");

  /*-------- First Program --------------------*/
  for (i = 0; i < SIZE; ++i) {
    if (a[i]) ++count1;
    klee_join("count", a, i, count1);
  }

  /*-------- Second Program -------------------*/
  for (i = 0; i < SIZE; ++i) {
    if (a[i]) ++count2;
  }

  assert(count1 == count2);
  return 0;
}
