/*
 * Example from urbina directory of
 * http://llbmc.org/files/downloads/llbmc-bench-1.1.tgz with KLEE
 * harness added.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <assert.h>
#include <klee/klee.h>
#endif
#include <stdlib.h>

int main()
{
  int nDim = 9;

  int bDomain = 1;
  int bNoCapture = 1;

  int ni, nj;


  int *n = malloc(nDim * sizeof(int));
  for (ni=0; ni<nDim; ni++) {
#ifdef LLBMC
    n[ni] = __llbmc_nondef_int();
#else
    int nonDet;
    klee_make_symbolic(&nonDet, sizeof(nonDet), "nonDet");
    n[ni] = nonDet;
#endif
  }

  for(ni=0; ni<nDim; ni++) {
    bDomain = bDomain && (n[ni] >= 0) && (n[ni] < nDim);
    for(nj=0; nj<nDim; nj++)
      if(ni!=nj) {
	bNoCapture = bNoCapture && (n[ni] != n[nj]);
	bNoCapture = bNoCapture && ni+n[nj] != nj+n[ni]
	  && ni+n[ni] != nj+n[nj];
      }
  }

#ifdef LLBMC
  __llbmc_assert(!(bDomain && bNoCapture));
#else
  klee_assert(!(bDomain && bNoCapture));
#endif
  free(n);

  return 0;
}
