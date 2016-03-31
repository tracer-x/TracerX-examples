/*
clang -emit-llvm -c wrong_loop_klee.c -o wrong_loop_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee wrong_loop_klee.o
*/
#include <assert.h>

int a[10];
int main(){
  int i,j;

  i=0;
  while(i<10){
    if(i==5){
      i=a[i];
      assert(a[i]>0);
    } else {
      j=i;
    }
    i++;
  }
  return 0;
}

