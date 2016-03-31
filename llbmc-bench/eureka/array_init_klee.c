/*
clang -emit-llvm -c array_init_klee.c -o array_init_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee array_init_klee.o 
*/
#include <assert.h>

int a[10];
int main(){
  int b[2];
  int i;
  i=0;
  while(i<10){
    a[i]=i+1;
    i=i+1;
  }
  if(a[8]==0){
    assert(0);
  } else {
    ;
  }
  return 0;
}
