/*
clang -emit-llvm -c simple_control_on_input_klee.c -o simple_control_on_input_klee.o
*/
#include <klee/klee.h>
#include <assert.h>

int i;
int a[20];

int main(){
  i=0;
  klee_make_symbolic(&i, sizeof(i), "i");
  if(i>0){
    while(i<20){
      a[i]=i;
      i=i+1;
    }
  } else {
      assert(0);
  }
  return 0;
}
