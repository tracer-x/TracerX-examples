/*
clang -g -emit-llvm -c simple_fail.c -o simple_fail.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee simple_fail.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>
int main(void) {
  int a;

  a = 1;
  a = -1;
  assert(a != -1);
  return a;
}

