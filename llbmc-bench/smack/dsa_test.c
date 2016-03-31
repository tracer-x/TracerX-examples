/*
clang -g -emit-llvm -c dsa_test.c -o dsa_test.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee dsa_test.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

void setArray(int *array) {
  array[3] = 1;
}

int main() {
  int *array = (int*)malloc(10 * sizeof(int));
  setArray(array);
  free(array);
  return 0;
}

