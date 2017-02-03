/*
cd
cd nus/kleetest/llbmc-bench/urbiva
clang -g -emit-llvm -c queens.c -o queens.bc
time ~/git/original/klee/Release+Asserts/bin/klee -only-output-states-covering-new queens.bc 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

int main()
{
    int nDim = 9;

    int bDomain = 1;
    int bNoCapture = 1;

    int ni, nj;


    int *n = malloc(nDim * sizeof(int));
    for (ni=0; ni<nDim; ni++) {
	int nonDet;
	klee_make_symbolic(&nonDet, sizeof(nonDet), "nonDet");
        n[ni] = nonDet;
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

    assert(!(bDomain && bNoCapture));
    free(n);

    return 0;
}
