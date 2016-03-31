/*
clang -emit-llvm -c simple_array_inversion_klee.c -o simple_array_inversion_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee simple_array_inversion_klee.o
*/
#include <assert.h>

int i,j;
int a[4];
int main(){
  a[0]=0;
  a[3]=3;
  j=0;
  while(j<2){
    a[j]=a[3-j];
    j=j+1;
  }
  if(a[0]==0){
  	assert(0);
  }
  return 0;
}
