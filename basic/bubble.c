/*
 * Bubble sort
 * 
 * From
 * http://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
 *
 * With the array modified to be a char array.
 */
#include <klee/klee.h>
#include <assert.h>

#define ARRAY_SIZE 4

int main() {
  char a[ARRAY_SIZE], swap;
  int c, d;
 
  klee_make_symbolic(a, ARRAY_SIZE * sizeof(a[0]), "a");

  for (c = 0 ; c < ( ARRAY_SIZE - 1 ); c++)
  {
    for (d = 0 ; d < ARRAY_SIZE - c - 1; d++)
    {
      if (a[d] > a[d+1]) /* For decreasing order use < */
      {
        swap       = a[d];
        a[d]   = a[d+1];
        a[d+1] = swap;
      }
    }
  }

  assert (a[0] <= a[1] &&
	  a[1] <= a[2] &&
	  a[2] <= a[3]);

  return 0;
}
