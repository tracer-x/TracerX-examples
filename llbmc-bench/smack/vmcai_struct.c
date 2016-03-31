/*
clang -g -emit-llvm -c vmcai_struct.c -o vmcai_struct.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee vmcai_struct.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

typedef struct {
  int x;
} S1;

typedef struct {
  int a;
  int b;
} S2;

int main(void) {
  S2* s2 = (S2*)malloc(sizeof(S2));
  S1* s1 = (S1*)s2;

  s2->a = 3;
  s2->b = 5;
  s1->x = 4;

  assert(s2->a == 4);
  return 0;
}

