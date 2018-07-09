#include <klee/klee.h>

int wcet;
int UB = 50000;
int B = 50000;
int LB = 50;


int main(void)
{
  wcet = 0;
  long int x;
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_assume(x >= 1);
  klee_assume(x <= 21);

  int n = 50;
  int      i;

  wcet++;

   if(x>1)         
    {
      wcet++;
      wcet++;
      wcet++;
      wcet++;
    }
  else 
    {
      wcet++;
      wcet++;
      for (i=1;i<=5;i++){
          wcet++;
          wcet++;  
      }
    }
 
  printf("Timing of Path:%d\n",wcet); 
  klee_assert(wcet <= B);
  return 0;
}

