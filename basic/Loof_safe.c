#include <assert.h>
#include <stdlib.h>
#include<klee/klee.h>

int main(){
 
   int i;
   int j;
   klee_make_symbolic(&i, sizeof(i), "i");   
   klee_make_symbolic(&j, sizeof(j), "j");   
   klee_assume (0 <= i);
   klee_assume (i <= 10);

   int x,y;
   x=i;
   y=j;

   while (x!=0) {
      x--;
      y--;
   }

   if (i==j){
      assert( y == 0);

      
   }
   
   
   return 1;
}
