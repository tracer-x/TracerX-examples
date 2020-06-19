#include <klee/klee.h>

#define N 10
#define BOUND 66
        
int choice(int v) {
   if (v != 1) v=0; 
   else v = 1;   
   return v;
}

int main() {
       int sum = 0;
       int GOAL = 0;
       int x = 0;
       for (x = 1; x<=N; x++) { // can choose in another order
           int v;
           klee_make_symbolic(&v, sizeof(unsigned), "v");
//         if (v != 1) v=0; 
//	   else v = 1;                                                                       
           v = choice(v); 
           sum += v * x;
           klee_assert(sum<=BOUND);
       }
}

