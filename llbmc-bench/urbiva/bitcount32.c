/*
clang -g -emit-llvm -c bitcount32.c -o bitcount32.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee bitcount32.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

#include <string.h>
#include <stdint.h>

uint32_t nBC1(uint32_t nX)
{
    uint32_t res = 0;
    size_t nI;
    for (nI = 0; nI < 8*sizeof(uint32_t); nI++) {
        res += (nX & (1 << nI)) ? 1 : 0;
    }
    return res;
}

uint32_t nBC2(uint32_t nX)
{
    uint32_t res = nX;
    res = (res & 0x55555555) + (res >> 1  & 0x55555555);
    res = (res & 0x33333333) + (res >> 2  & 0x33333333);
    res = (res & 0x0F0F0F0F) + (res >> 4  & 0x0F0F0F0F);
    res = (res & 0x00FF00FF) + (res >> 8  & 0x00FF00FF);
    res = (res & 0x0000FFFF) + (res >> 16 & 0x0000FFFF);
    return res;
}

int main()
{
    int nX;
    klee_make_symbolic(&nX, sizeof(nX), "nX");
    assert(nBC1(nX) == nBC2(nX));
    return 0;
}
