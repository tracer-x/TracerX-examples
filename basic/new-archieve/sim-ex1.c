#include <klee/klee.h>

#define N 10
#define BOUND 66
int weight[] = {0,1,2,3,4,5,6,7,8,9,10};
int GOAL = 0;

   
int main() {
       int sum = 0;
       int x = 0;
       for (x = 1; x<=N; x++) { 
           int v;
           klee_make_symbolic(&v, sizeof(unsigned), "v");
           if (v != 0) v=1; else v = 0;                                                                       
           sum += v * weight[x];
	   if (sum > BOUND) exit(0);
	   if (x == N) {printf("Sum:%d\n",sum); exit(0);} 
       }
       printf("Sum:%d\n",sum);
}

