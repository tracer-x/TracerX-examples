/*
clang -g -emit-llvm -c dsa_test2.c -o dsa_test2.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee dsa_test2.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

int *a;

void set(int *x) {
  *x = 1;
}

int main() {
  int y;
  a = &y;
  *a = 2;
  set(&y);
  return 0;
}

