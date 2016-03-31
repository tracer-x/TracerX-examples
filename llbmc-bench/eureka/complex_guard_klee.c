/*
clang -emit-llvm -c complex_guard_klee.c.c -o complex_guard_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee complex_guard_klee.o
*/
#include <assert.h>

int main() {
    int i;
    int a[3];

    a[1] = 0;
    i = 0;
    while((a[i]!=0)&&(i<3)){
      a[i] = 2*i;
      i = i+1;
    }
    if(i>=2){
    	assert(0);
    } else {
      ;
    }
    return 0;
}
