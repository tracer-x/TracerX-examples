/*
clang -g -emit-llvm -c array1.c -o array1.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee array1.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

#define MAXSIZE 50
#define RESET 0

int main() {
  int *a = (int*)malloc(MAXSIZE * sizeof(int));

  a[5] = 10;

  assert(a[5] == 10);

  free(a);
  return 0;
}

