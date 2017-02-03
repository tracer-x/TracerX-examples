/*
 * Example from urbina directory of
 * http://llbmc.org/files/downloads/llbmc-bench-1.1.tgz with KLEE
 * harness added.
 */
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

int main()
{
  int nDim = 12;

  int bDomain = 1;
  int bAllDiff = 1;
  int bGray = 1;

  int ni, nj;

  int *na = malloc(nDim * sizeof(int));
  int nonDet;
  klee_make_symbolic(&nonDet, sizeof(nonDet), "nonDet");

  for (ni = 0; ni < nDim; ni++) {
    na[ni] = nonDet;
  }

  for (ni = 0; ni < nDim; ni++) {
    bDomain = bDomain && (0 <= na[ni]) && (na[ni] < nDim);
  }

  for (ni = 0; ni < nDim - 1; ni++) {
    for (nj = ni + 1; nj < nDim; nj++) {
      bAllDiff = bAllDiff && (na[ni] != na[nj]);
    }
  }

  for (ni = 0; ni < nDim - 1; ni++) {
    int nDiff = na[ni] ^ na[ni + 1];
    bGray = bGray && !(nDiff & (nDiff - 1)) && (nDiff != 0);
  }

  assert(!(bDomain && bAllDiff && bGray));
  free(na);

  return 0;
}
