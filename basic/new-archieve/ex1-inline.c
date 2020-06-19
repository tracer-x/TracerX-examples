#include <klee/klee.h>

#define N 10
#define BOUND 66
//int sum = 0;
//int weight[] = {0,1,2,3,4,5,6,7,8,9,10};
//int GOAL = 0;

//int check_infeasible() {  if (sum > BOUND) exit(0); }
int check_goal(int x, int sum) { if (x == N) {printf("Sum:%d\n",sum); exit(0);} }

        
/*int choice(int z, char *ch) {
    //if (*ch == '\0') exit(0);
    //if (z != *ch) choice(z, ch + 1);
    if (z != 0) z=1; 
    else z = 0;                                                                       
    return z;
}

int sim(int x, int v) {
   sum += v * weight[x];
   check_infeasible();
   check_goal(x);
}*/
    
int main() {
       int sum = 0;
       int weight[] = {0,1,2,3,4,5,6,7,8,9,10};
       int GOAL = 0;
       int x = 0;
       for (x = 1; x<=N; x++) { // can choose in another order
           int v;
           klee_make_symbolic(&v, sizeof(unsigned), "v");
           //if (x % 2) choice(v, "01"); else choice(v, "10");
           //v = choice(v, "10");  
           if (v != 0) v=1; else v = 0;                                                                       
           //sim(x, v);
           sum += v * x;
	   //check_infeasible();
	   if (sum > BOUND) exit(0);
	   //check_goal(x, sum);
	   if (x == N) {printf("Sum:%d\n",sum); exit(0);} 
       }
       printf("Sum:%d\n",sum);
}

