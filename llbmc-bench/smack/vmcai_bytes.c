/*
clang -g -emit-llvm -c vmcai_bytes.c -o vmcai_bytes.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee vmcai_bytes.o 
*/
#include <stdlib.h>
#include <klee/klee.h>
#include <assert.h>

int main() {
  int x = 0;
  char* p = (char*)&x;
  p[2] = 1;

  assert(x != 0);

  return 0;
}

