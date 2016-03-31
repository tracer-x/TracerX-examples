/*
clang -emit-llvm -c bf5_klee.c -o bf5_klee.o
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/original/klee/Release+Asserts/bin/klee bf5_klee.o 
*/
#include <assert.h>

int INFINITY = 899;
int main(){
  int nodecount = 5;
  int edgecount = 5;
  int source = 0;
  int Source[5] = {0,0,0,3,4};
  int Dest[5] = {1,0,0,1,1};
  int Weight[5] = {0,1,2,3,4};
  int distance[5];
  klee_make_symbolic(distance, sizeof(distance), "distance"); 
  int x,y;
  int i,j;

  for(i = 0; i < nodecount; i++){
    if(i == source){
      distance[i] = 0;
    }
    else {
      distance[i] = INFINITY;
    }
  }

  for(i = 0; i < nodecount; i++)
    {
      for(j = 0; j < edgecount; j++)
        {
          x = Dest[j];
          y = Source[j];
          if(distance[x] > distance[y] + Weight[j])
            {
              distance[x] = distance[y] + Weight[j];
            }
        }
    }
  for(i = 0; i < edgecount; i++)
    {
      x = Dest[i];
      y = Source[i];
      if(distance[x] > distance[y] + Weight[i])
        {
          return 0;
        }
    }

  for(i = 0; i < nodecount; i++)
    {
      assert(distance[i]>=0);
    }

  return 0;
}
