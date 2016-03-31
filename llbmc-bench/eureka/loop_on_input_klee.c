/*
clang -emit-llvm -c loop_on_input_klee.c -o loop_on_input_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee loop_on_input_klee.o
*/
#include <assert.h>

int main(){
  int x,i;
  x=5;
  while(x<4){
    if(x>0){
      x=x+1;
    } else {
      x=1;
    }
  }
  assert(0);
  return 0;
}
