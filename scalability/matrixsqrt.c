/*
 * Example from urbina directory of
 * http://llbmc.org/files/downloads/llbmc-bench-1.1.tgz with KLEE
 * harness added.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include <stdlib.h>

int main()
{
  int nDim = 2;
   
  int ni, nj, nk;

  int *nM = malloc(nDim*nDim*sizeof(int));
  int *nA = malloc(nDim*nDim*sizeof(int));
  for (ni = 0; ni < nDim; ni++)
    for (nj = 0; nj < nDim; nj++){
#ifdef LLBMC
      nA[nDim * ni + nj] = __llbmc_nondef_int();
#else
      int nonDet;
      klee_make_symbolic(&nonDet, sizeof(nonDet), "nonDet");        
      nA[nDim*ni+nj] = nonDet;
#endif
    }
  for (ni = 0; ni < nDim; ni++)
    for (nj = 0; nj < nDim; nj++) {
      nM[nDim*ni+nj] = 0;
      for (nk = 0; nk < nDim; nk++)
	nM[nDim*ni+nj] = nM[nDim*ni+nj] + nA[nDim*ni+nk]*nA[nDim*nk+nj];
    }

#ifdef LLBMC
  __llbmc_assert(!(nM[nDim * 0 + 0] == 19 && nM[nDim * 0 + 1] == 22 &&
                   nM[nDim * 1 + 0] == 43 && nM[nDim * 1 + 1] == 50));
#else
  klee_assert(!(nM[nDim * 0 + 0] == 19 && nM[nDim * 0 + 1] == 22 &&
                nM[nDim * 1 + 0] == 43 && nM[nDim * 1 + 1] == 50));
#endif
  free(nM);
  free(nA);

  return 0;
}
