/*
clang -g -emit-llvm -c dsa_test3.c -o dsa_test3.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee dsa_test3.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

typedef struct {
  char pero;
  int *status;
  int *y;
  int x;
} elem;

void setArray(elem *array) {
  *(array->status) = 20;
  array->x = 3;
}

int main() {
  elem *array = (elem*)malloc(sizeof(elem));
  array->status = (int*)malloc(sizeof(int));
  setArray(array);
  free(array->status);
  free(array);
  return 0;
}

