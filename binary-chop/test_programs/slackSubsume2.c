#include <klee/klee.h>

int main() {
  int wcet;
  int a,b;


  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");

  wcet = 0;

  if (a < 0){
     wcet +=51;
  }else{
     wcet+=50;
  }
  
  if (b < 0){
     wcet +=1;
  }else{
     wcet+=2;
  }
  
  
  if (a != 1){
     wcet += 49;
  }else{
     wcet += 50;
  }

  klee_assert(wcet < 104);
  
} 
