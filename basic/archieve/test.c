
#include <klee/klee.h>

int main() {
  int x;
  klee_make_symbolic(&x, sizeof(x), "x");
  
  if (x < 0){
     x = -x;
     
  }
  tracerx_memo_check(5,1,2,3,4,5);
  tracerx_memo(5,1,2,3,4,5);
  printf("We reached here.\n");
} 
