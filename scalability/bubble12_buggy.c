/*
 * Bubble sort
 * 
 * Copyright 2016 National University of Singapore 
 *
 * This is an example whose analysis by naive path
 * exploration is expensive. Note that the paper
 * "Sorting nine inputs requires twenty-five comparisons"
 * by Codish et al. http://arxiv.org/abs/1405.5754
 * suggests that in standard sorting algorithm there can 
 * possibly be plenty of superfluous comparisons.
 *
 * This is the version with 12 array elements and
 * an injected program error to test the difference
 * in tool behavior.
 */
#include <klee/klee.h>
#include <assert.h>

#define ARRAY_SIZE 12

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

  // This is the bug, where the
  // last two elements are re-swapped.
  int tmp = a[11];
  a[11] = a[10];
  a[10] = tmp;

  assert (a[0] <= a[1] &&
	  a[1] <= a[2] &&
	  a[2] <= a[3] &&
	  a[3] <= a[4] &&
	  a[4] <= a[5] &&
	  a[6] <= a[7] &&
	  a[7] <= a[8] &&
	  a[8] <= a[9] &&
	  a[9] <= a[10] &&
	  a[10] <= a[11]);
}
