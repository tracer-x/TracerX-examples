#include <klee/klee.h>

#define N 2
#define WBOUND 5
#define PBOUND 100
int weight[4] = {1, 2, 1, 3}; int profit[4] = {12, 21, 10, 29};
int p = 0, w = 0; // system state
int v = 0;

int main() {
    int output = search();
    printf("Output %d Profit %d, Weight %d\n", output, p,w);
}

int search(){
  int a = choice();
  if (!sim(v, a))
      if (goal()) exit(p); else return 0;
  if (goal()) return 0;
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


int sim(int v, int a)
{
  if(a) {p+=profit[v]; w+=weight[v];}
  if(p > PBOUND) return 0;
  if(w > WBOUND) return 0;
  return 1;
} 

int goal() 
{
  if(v == 3) return 1;
  else return 0;
}
