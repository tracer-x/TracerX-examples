/*
clang -g -emit-llvm -c send-more-money.c -o send-more-money.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee send-more-money.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

int main()
{
    unsigned int nS;
    unsigned int nE;
    unsigned int nN;
    unsigned int nD;
    unsigned int nM;
    unsigned int nO;
    unsigned int nR;
    unsigned int nY;

    klee_make_symbolic(&nS, sizeof(nS), "nS");
    klee_make_symbolic(&nE, sizeof(nE), "nE");
    klee_make_symbolic(&nN, sizeof(nN), "nN");
    klee_make_symbolic(&nD, sizeof(nD), "nD");
    klee_make_symbolic(&nM, sizeof(nM), "nM");
    klee_make_symbolic(&nO, sizeof(nO), "nO");
    klee_make_symbolic(&nR, sizeof(nR), "nR");
    klee_make_symbolic(&nY, sizeof(nY), "nY");

    int bAllDifferent;
    int bDomain;
    int bNoLeadingZeros;
    int bSum;

    bAllDifferent =                  (nS != nE) && (nS != nN) && (nS != nD) && (nS != nM) && (nS != nO) && (nS != nR) && (nS!=nY);
    bAllDifferent = bAllDifferent && (nE != nN) && (nE != nD) && (nE != nM) && (nE != nO) && (nE != nR) && (nE != nY);
    bAllDifferent = bAllDifferent && (nN != nD) && (nN != nM) && (nN != nO) && (nN != nR) && (nN != nY);
    bAllDifferent = bAllDifferent && (nD != nM) && (nD != nO) && (nD != nR) && (nD!=nY);
    bAllDifferent = bAllDifferent && (nM != nO) && (nM != nR) && (nM != nY);
    bAllDifferent = bAllDifferent && (nO != nR) && (nO != nY);
    bAllDifferent = bAllDifferent && (nR != nY);
    bDomain = (nS < 10) && (nE < 10) && (nN < 10) && (nD < 10) && (nM < 10) && (nO < 10) && (nR < 10) && (nY < 10);
    bNoLeadingZeros = (nM != 0) && (nS != 0);
    bSum =            nS*1000 + nE*100 + nN*10 + nD +
                      nM*1000 + nO*100 + nR*10 + nE   ==
           nM*10000 + nO*1000 + nN*100 + nE*10 + nY;

    assert(!(bAllDifferent && bDomain && bNoLeadingZeros && bSum));
    return 0;
}
