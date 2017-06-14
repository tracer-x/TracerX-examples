/*
 * From Figure 11 in Cadar, Dunbar, Engler: KLEE: Unassisted and
 * Automatic Generation of High-Coverage Tests for Complex Systems
 * Programs, OSDI '08.
 * 
 * make clean
 * clang -emit-llvm -g -c mod_eq.c
 * time /home/felicia/git/tracerx/klee/Release+Asserts/bin/klee -max-time=10 -output-tree -write-pcs -use-query-log=all:pc,all:smt2 -allow-external-sym-calls -search=dfs -select-solver=stp -output-dir=mod_eq.stpklee mod_eq.bc -max-fail 1
 */

#include <klee/klee.h>
#include<stdio.h>
#include <assert.h>

unsigned mod_opt(unsigned x, unsigned y) {
  if((y & -y) == y) { 
    return x & (y-1);
  }
  else{
    return x % y;
  }
}

unsigned mod(unsigned x, unsigned y) {
  return x % y;
}

int main() {
  unsigned x,y;
  
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");
  klee_assume(x <= 10);
  klee_assume(y <= 10);
  assert(mod(x,y) == mod_opt(x,y));
  return 0;
}
