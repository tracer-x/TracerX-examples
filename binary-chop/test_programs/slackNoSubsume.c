#include <klee/klee.h>

int wcet;
int main() {
  int a,b,q;


  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");

  wcet = 0;
  q = 5;

  if (a >= 0){
     wcet += 5;
     q +=3;
  }else{
     wcet += 2;
     q +=4;
  }
  
  if (b > 0){
     wcet += 96;
     q +=5;
  }else{
     wcet += 94;
     q +=6;
  }

  klee_assert(wcet <= 100);
  
} 
