/*
 * Bubble sort
 * 
 * Copyright 2016 National University of Singapore 
 */
#include <klee/klee.h>
#include <assert.h>

#define ARRAY_SIZE 3

int main() {
  int a[ARRAY_SIZE];

  klee_make_symbolic(a, ARRAY_SIZE * sizeof(int), "a");

  for (int i=0; i < ARRAY_SIZE - 2; i++) {
    for (int j=i; j < ARRAY_SIZE - 1; j++) {
      if (a[j] > a[j+1]) {
	int tmp = a[j];
	a[j+1] = a[j];
	a[j] = tmp;
      }
    }
  }

  assert (a[0] <= a[1] &&
	  a[1] <= a[2]);
}
