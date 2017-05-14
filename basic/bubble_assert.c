/*
 * Bubble sort
 *
 * From
 * http://www.programmingsimplified.com/c/source-code/c-program-bubble-sort
 *
 * With the array modified to be a char instead of int array and with
 * correctness assertion added.
 *
 * This is an example whose analysis by naive path exploration is
 * expensive. Note that the paper "Sorting nine inputs requires
 * twenty-five comparisons" by Codish et
 * al. http://arxiv.org/abs/1405.5754 suggests that in standard
 * sorting algorithm there can possibly be plenty of superfluous
 * comparisons.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <assert.h>
#include <klee/klee.h>
#endif

#define ARRAY_SIZE 4

int main() {
  char a[ARRAY_SIZE], swap;
  int n, c, d;

#ifdef LLBMC
  for (int i = 0; i < ARRAY_SIZE; ++i) {
    a[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(a, ARRAY_SIZE * sizeof(a[0]), "a");
#endif

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

#ifdef LLBMC
  __llbmc_assert(a[0] <= a[1] && a[1] <= a[2] && a[2] <= a[3]);
#else
  klee_assert(a[0] <= a[1] && a[1] <= a[2] && a[2] <= a[3]);
#endif

  return 0;
}
