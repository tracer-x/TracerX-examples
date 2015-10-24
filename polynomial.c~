/*
cd
cd nus/kleetest
llvm-gcc --emit-llvm -c -g polynomial.c
opt -analyze -dot-cfg polynomial.o
klee -use-query-log=all:pc,all:smt2 -search=dfs polynomial.o
ktest-tool --write-ints klee-last/test000001.ktest
ktest-tool --write-ints klee-last/test000002.ktest

*/
#include <assert.h>

int polynomial(int p1, int p2) { 
int x = 0;
 if(((2*(p1^3)) - (p1^2) - (7*p1) + 2) == 0) //p1=2
	x = x + 2;
 if(p2 > 5)
	x = x * 2;
 return x;
} 

int main() {
  int p1,p2;
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  return polynomial(p1, p2);
} 
//2*p1^3 - p1^2 - 7*p1 + 2
