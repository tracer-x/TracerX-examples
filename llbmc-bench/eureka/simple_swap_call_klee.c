/*
clang -emit-llvm -c simple_swap_call_klee.c -o simple_swap_call_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee simple_swap_call_klee.o
*/
#include <assert.h>

int a[2];
int i,j,tmp;
int main(){
  i=0;
  j=1;
  a[i]=100;
  a[j]=200;
  tmp=a[i];
  a[i]=a[j];
  a[j]=tmp;
  if(a[i]==100){
    assert(0);
  } else {
    ;
  }
  return 0;
}
