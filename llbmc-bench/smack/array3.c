/*
clang -g -emit-llvm -c array3.c -o array3.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee array3.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

#define MAXSIZE 50
#define RESET 0

void initializeArray(int *array) {
  int i = 0;

  for (i = 0; i < MAXSIZE; i++) {
    array[i] = RESET;
  }
}


int main() {
  int i = 0;
  int *array = (int*)malloc(MAXSIZE * sizeof(int));

  initializeArray(array);

  for (i = 0; i < MAXSIZE; i++) {
    assert(array[i] == RESET);
  }

  free(array);
  return 0;
}

