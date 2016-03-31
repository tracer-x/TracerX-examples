/*
clang -g -emit-llvm -c simple_pre.c -o simple_pre.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee simple_pre.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

int returnOne() {
  return 1;
}

int main(void) {
  int a;

  a = -1;
  a = returnOne();
  assert(a == 1);
  return a;
}

