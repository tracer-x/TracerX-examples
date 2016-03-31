/*
cd
cd nus/kleetest/llbmc-bench/eureka
clang -emit-llvm -c bubblesort_klee.c -o bubblesort_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee -only-output-states-covering-new -allow-external-sym-calls bubblesort_klee.o 
ktest-tool --write-ints klee-last/test000001.ktest
ktest-tool --write-ints klee-last/test000002.ktest
*/
#include <assert.h>
#include <stdio.h>

int N=15;
int a[15];

void swap(int x,int y){
  int tmp;
  tmp=a[x];
  a[x]=a[y];
  a[y]=tmp;
}

int main(){
  int j,i;
  /*a[0]=0;
  a[1]=1;
  a[2]=2;
  a[3]=3;
  a[4]=4;
  a[5]=5;
  a[6]=6;
  a[7]=7;
  a[8]=8;
  a[9]=9;*/
  klee_make_symbolic(a, sizeof(a), "a");
  j=0;
  i=N-1;
  while(i>=0){
    while(j<i){
      if(a[j]<=a[j+1]){
        swap(j,j+1);
        ;
      } else {
        ;
      }
      j=j+1;
    }
    i=i-1;
  }
 /* printf("after sorted: \n");
  for(int w = 0; w < 10; w++){
  	printf("%d ", a[w]);
  }

  if(a[4]!=4){
    assert(0);
  }*/

  for (int w = 0; w < N - 1; w++) {
      assert(a[w] <= a[w + 1]);
  }
  
return 0;
}
