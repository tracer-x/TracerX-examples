/*
clang -g -emit-llvm -c array4.c -o array4.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee array4.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>
#define MAXSIZE 50
#define RESET 0

typedef struct {
  short data;
  int count;
  char status;
} elem;

void initializeArray(elem *array) {
  int i = 0;

  for (i = 0; i < MAXSIZE; i++) {
    array[i].status = RESET;
  }
}

int main() {
  int i = 0;
  elem *array = (elem*)malloc(MAXSIZE * sizeof(elem));

  initializeArray(array);

  for (i = 0; i < MAXSIZE; i++) {
	assert(array[i].status == RESET);
  }

  free(array);
  return 0;
}

