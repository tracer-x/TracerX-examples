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
  int bDomain = 1;
  int bSorted = 1;
  int nDim = 10;

  int *nA, *nB;
  int ni, nj;
  int nonDet;
  klee_make_symbolic(&nonDet, sizeof(nonDet), "nonDet");

  nA = malloc(nDim * sizeof(int));
  nA[0] = 5;
  nA[1] = 9;
  nA[2] = 4;
  nA[3] = 1;
  nA[4] = 3;
  nA[5] = 2;
  nA[6] = 6;
  nA[7] = 8;
  nA[8] = 0;
  nA[9] = 7;

  nB = malloc(nDim * sizeof(int));
  for (ni=0; ni<nDim; ni++) {
    nB[ni] = nonDet;
  }

  for (ni = 0; ni < nDim; ni++) {
    int bExists = 0;
    for (nj = 0; nj < nDim; nj++) {
      bExists = bExists || nA[ni] == nB[nj];
    }
    bDomain = bDomain && bExists;
  }

  for (ni = 0; ni < nDim - 1; ni++)
    bSorted = bSorted && (nB[ni] < nB[ni+1]);

#ifdef LLBMC
  __llbmc_assert(!(bDomain && bSorted));
#else
  klee_assert(!(bDomain && bSorted));
#endif
  free(nA);
  free(nB);

  return 0;
}
