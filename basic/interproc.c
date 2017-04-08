/*
Copyright 2015, 2017 National University of Singapore 
cd
cd nus/kleetest
llvm-gcc --emit-llvm -c -g interproc.c
llvm-gcc -S --emit-llvm interproc.c
opt -analyze -dot-cfg interproc.o
klee -write-pcs -use-query-log=all:pc,all:smt2 -search=dfs interproc.o
ktest-tool --write-ints klee-last/test000001.ktest
ktest-tool --write-ints klee-last/test000002.ktest
ktest-tool --write-ints klee-last/test000003.ktest

*/
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int y;

int add1(int p1, int x) {
  if (p1 > 8)
    return x + 1;
  return x;
}

int add2(int p2, int x) {
  if (p2 > 8)
    return x;
  return x + 2;
}

int add3(int p3, int x) {
  if (p3 > 8)
    return x;
  return x + 3;
}

int add(int p1, int p2, int p3, int x) { 
  if(x <= 0){
    x = add1(p1, x);
    x = add2(p2, x);
    x = add3(p3, x);
#ifdef LLBMC
    __llbmc_assert(x <= 6);
#else
    assert(x <= 6);
#endif
  }
  return x;
}

int main() {
  int p1, p2, p3;
  
#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  y = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&y, sizeof(y), "y");
#endif
  
  return add(p1, p2, p3, y);
} 
