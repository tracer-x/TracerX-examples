#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <klee/klee.h>



int main(int argc, char **argv) {

  int a,b,c;
  klee_make_symbolic(a, sizeof(int), "a");
  klee_make_symbolic(b, sizeof(int), "b");
  klee_assue( a >= 0);
  klee_assue( a <= 2);
    
    
  if (a > 1)   
  	printf("First\n");  
  	
  if (b >= 0)   
  	b = 4;
  else 
  	b = 5;
  
  if (a == 2)   
  	printf("Second\n");  
  	
  klee_assert(a != 2);
  return 0;


}
