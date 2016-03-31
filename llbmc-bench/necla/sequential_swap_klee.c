/*
clang -emit-llvm -c sequential_swap_klee.c -o sequential_swap_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee sequential_swap_klee.o
*/
#include <assert.h>

int a[2];
int i,j;

void p(){
  int tmp;
  tmp=a[i];
  a[i]=a[j];
  a[j]=tmp;
}

int main(){
  i=0;
  j=1;
  a[i]=100;
  a[j]=200;
  p();
  ;
  p();
  ;
  p();
  ;
  if(a[i]==100){
    assert(0);
  } else {
    ;
  }
  return 0;
}

