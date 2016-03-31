/*
clang -g -emit-llvm -c dsa_test4.c -o dsa_test4.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee dsa_test4.o 
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
  array[3].x = 33;
  array[3].status = NULL;
  array[5].x = 55;
  array[5].status = NULL;
  array[8].x = 88;
  array[8].status = NULL;
}

int main() {
  elem *array = (elem*)malloc(10 * sizeof(elem));
  setArray(array);
  free(array);
  return 0;
}

