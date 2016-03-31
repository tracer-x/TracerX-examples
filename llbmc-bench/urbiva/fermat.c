/*
clang -g -emit-llvm -c fermat.c -o fermat.bc
time ~/git/original/klee/Release+Asserts/bin/klee fermat.bc 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

uint32_t nPow(uint32_t nx, int np) {
    uint32_t nPow = 1;
    int ni;
    for (ni = 0; ni < np; ni++) {
        nPow *= nx;
    }
    return nPow;
}

void main() {  
    uint32_t na;
    uint32_t nb;
    uint32_t nc;
    klee_make_symbolic(&na, sizeof(na), "na");
    klee_make_symbolic(&nb, sizeof(nb), "nb");
    klee_make_symbolic(&nc, sizeof(nc), "nc");
    int nN = 3;
    klee_assume(na > 0);
    klee_assume(nb > 0);
    klee_assume(nc > 0);
    assert(nPow(na, nN) + nPow(nb, nN) != nPow(nc, nN));
}
