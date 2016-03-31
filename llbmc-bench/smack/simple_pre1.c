/*
clang -g -emit-llvm -c simple_pre1.c -o simple_pre1.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee simple_pre1.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

int incr(int x) {
  return x;
}

int main(void) {
  int a;

  a = -1;
  a = incr(a);
  assert(a == -1);
  return a;
}

