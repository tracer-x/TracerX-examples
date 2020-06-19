#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#define N 4 // processes 0, 1, 2, 3 each with 4 rules
#define M 4 // number of rules for each process
#define BOUND 3
int left[N], right[N];
int starve[N] = {0};
int eating = 0, caneat[N] = {1};
int main() {
int choice;
for (int i = 0 ; i < BOUND; i++) {
   klee_make_symbolic(&choice, sizeof(int), "choice");
   int c = choice % 16;
   switch (c) {
       // P0
       case 0:  if (!left[0] && !right[N-1]) left[0] = 1; break;
       case 1:  if (!right[0] && !left[1]) right[0] = 1; break;
       case 2:  if (left[0] == 1 && right[0] == 1 && caneat[0]) { caneat[0] = 0; eating++; starve[0]++; break;}
       case 3:  if (left[0] == 1 && right[0] == 1 && !caneat[0]) { caneat[0] = 0; eating++; starve[0]++; break;}
       // P1
       case 4:  if (!left[1] && !right[0]) left[1] = 1; break;
       case 5:  if (!right[1] && !left[2]) right[1] = 1; break;
       case 6:  if (left[1] == 1 && right[1] == 1 && caneat[1]) { caneat[1] = 0; eating++; starve[1]++; break;}
       case 7:  if (left[1] == 1 && right[1] == 1 && !caneat[1]) { caneat[1] = 1; eating--; left[1] = right[1] = 0; break;}
       // P2
       case 8:  if (!left[2] && !right[1]) left[2] = 1; break;
       case 9:  if (!right[2] && !left[3]) right[2] = 1; break;
       case 10: if (left[2] == 1 && right[2] == 1 && caneat[2]) { caneat[2] = 0; eating++; starve[2]++; break;}
       case 11: if (left[2] == 1 && right[2] == 1 && caneat[2]) { caneat[2] = 1; eating--; left[2] = right[1] = 0; break;}

 
       // add code for different N ....
         

   }
   klee_assert(eating <= N/2); // (1)
}
klee_assert(!starve[0]); // (2)
return 0;
}

