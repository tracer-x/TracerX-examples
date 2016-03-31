/*
clang -emit-llvm -c array_init_assign_klee.c -o array_init_assign_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee array_init_assign_klee.o 
*/
#include <assert.h>

int a[2];
int main(){
  int i,j;
  i=0;
  while(i<2){
    a[i]=0;
    i=i+1;
  }
  j=0;
  while(j<2){
    a[j]=j+1;
    j=j+1;
  }
  if(a[1]==0){
    assert(0);
  } else {
    ;
  }
  return 0;
}
