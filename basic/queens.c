/*
 * Example from urbina directory of
 * http://llbmc.org/files/downloads/llbmc-bench-1.1.tgz with KLEE
 * harness added.
 *
 * Here we changed the board size from 8 to 4, changed the malloc()
 * call into local array, and the size declaration into the SIZE
 * macro. In some version of Tracer-X KLEE, this exhibits
 * over-subsumption such that the assertion violation is unreported.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <assert.h>
#include <klee/klee.h>
#endif
#include <stdlib.h>

#define SIZE 4

int main()
{
  int bDomain = 1;
  int bNoCapture = 1; /* Changing the type of bNoCapture to char
                         results in assertion triggered. */

  int ni, nj;

  int n[SIZE];
#ifdef LLBMC
  for (ni=0; ni<SIZE; ni++) {
    n[ni] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(n, SIZE * sizeof(int), "n");
#endif

  for(ni=0; ni<SIZE; ni++) {
    bDomain = bDomain && (n[ni] >= 0) && (n[ni] < SIZE);
    for(nj=0; nj<SIZE; nj++)
      if(ni!=nj) {
        bNoCapture = bNoCapture && (n[ni] != n[nj]);
        bNoCapture = bNoCapture && ni+n[nj] != nj+n[ni]
          && ni+n[ni] != nj+n[nj];
      }
  }

  /*
   * If the assertion was violated, then there is a solution. That
   * means, the domains are respected and there is no capturing.
   */
#ifdef LLBMC
  __llbmc_assert(!(bDomain && bNoCapture));
#else
  klee_assert(!(bDomain && bNoCapture));
#endif

  return 0;
}
