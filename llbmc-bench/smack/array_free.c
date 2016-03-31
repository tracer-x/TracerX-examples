/*
clang -g -emit-llvm -c array_free.c -o array_free.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee array_free.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

#define MAXSIZE 42

typedef struct _DATA DATA, *PDATA;

struct _DATA {
  int *f;
};

DATA a[MAXSIZE];

void free_array() {
  int i;

  for (i = 0; i < MAXSIZE; i++) {
    if (a[i].f != 0) {
      free(a[i].f);
      a[i].f = 0;
    }
  }
}

int main() {
  free_array();
  return 0;
}

