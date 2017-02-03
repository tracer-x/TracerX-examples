/*
clang -g -emit-llvm -c matrixsqrt.c -o matrixsqrt.bc
time ~/git/original/klee/Release+Asserts/bin/klee matrixsqrt.bc 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>


int main()
{
    int nDim = 2;
   
    int ni, nj, nk;

    int *nM = malloc(nDim*nDim*sizeof(int));
    int *nA = malloc(nDim*nDim*sizeof(int));
    for (ni = 0; ni < nDim; ni++)
        for (nj = 0; nj < nDim; nj++){
	    int nonDet;
            klee_make_symbolic(&nonDet, sizeof(nonDet), "nonDet");        
	    nA[nDim*ni+nj] = nonDet;
	}
    for (ni = 0; ni < nDim; ni++)
        for (nj = 0; nj < nDim; nj++) {
            nM[nDim*ni+nj] = 0;
            for (nk = 0; nk < nDim; nk++)
                nM[nDim*ni+nj] = nM[nDim*ni+nj] + nA[nDim*ni+nk]*nA[nDim*nk+nj];
        }

    assert(!(nM[nDim*0+0] == 19 && nM[nDim*0+1] == 22 && nM[nDim*1+0] == 43  && nM[nDim*1+1] == 50));
    free(nM);
    free(nA);

    return 0;
}
