#include <klee/klee.h>

#define N 2
#define WBOUND 5
#define PBOUND 100
int weight[4] = {1, 2, 1, 3}; 
int w = 0; // system state
int v = 0;

int main() {
    int output = search();
    printf("Output %d Weight %d\n", output, w);
}

int search(){
  int a = choice();
  sim(a);
  if(v == 3) return 1;
  v++;
  search();
  return 1;
}

int choice() {
  int c,z = -1;
  c = klee_range(0, N, "c");
  for(int i = 0;i<=c;i++){
      z = i;
  }
  if (z == -1) exit(0);
  return z;
}


int sim(int a)
{
  if(a) {w+=weight[v];}
} 

