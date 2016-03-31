/*
clang -g -emit-llvm -c array2.c -o array2.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee array2.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

#define MAXSIZE 50
#define RESET 0

int main() {
  int i = 0;
  int *a = (int*)malloc(MAXSIZE * sizeof(int));

  for (i = 0; i < MAXSIZE; i++) {
    a[i] = RESET;
  }

  assert(a[5] == RESET);

  free(a);
  return 0;
}

