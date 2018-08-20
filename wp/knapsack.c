#include <klee/klee.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHOICE 100
#define MAXWEIGHT 483
#define N 10
#define BOUND 483

//int choice[MAXCHOICE], *choice_ptr;

int knapsack0, knapsack1, knapsack2, knapsack3, knapsack4, knapsack5, knapsack6, knapsack7, knapsack8, knapsack9;

int main() {
  int i, j, exp = 2, sum = 0, w = 0, p = 0;
  for (i = 0; i < N; i++) {
    int choice;
    klee_make_symbolic(&choice, sizeof(int), "choice");
    if (choice > 0) {
      w += i;
      p += 2*i;
      if (i==0) {
        knapsack0 = 2*i;
      } else if(i==1) {
        knapsack1 = 2*i;
      } else if(i==2) {
        knapsack2 = 2*i;
      } else if(i==3) {
        knapsack3 = 2*i;
      } else if(i==4) {
        knapsack4 = 2*i;
      } else if(i==5) {
        knapsack5 = 2*i;
      } else if(i==6) {
        knapsack6 = 2*i;
      } else if(i==7) {
        knapsack7 = 2*i;
      } else if(i==8) {
        knapsack8 = 2*i;
      } else if(i==9) {
        knapsack9 = 2*i;
      }
    }
    
    if (i == N - 1) {
      for (j = 0; j <= i; j++) {
        if (j==0) {
          printf("%d:%d ", j, knapsack0);
          sum += knapsack0;
        } else if(j==1) {
          printf("%d:%d ", j, knapsack1);
          sum += knapsack1;
        } else if(j==2) {
          printf("%d:%d ", j, knapsack2);
          sum += knapsack2;
        } else if(j==3) {
          printf("%d:%d ", j, knapsack3);
          sum += knapsack3;
        } else if(j==4) {
          printf("%d:%d ", j, knapsack4);
          sum += knapsack4;
        } else if(j==5) {
          printf("%d:%d ", j, knapsack5);
          sum += knapsack5;
        } else if(j==6) {
          printf("%d:%d ", j, knapsack6);
          sum += knapsack6;
        } else if(j==7) {
          printf("%d:%d ", j, knapsack7);
          sum += knapsack7;
        } else if(j==8) {
          printf("%d:%d ", j, knapsack8);
          sum += knapsack8;
        } else if(j==9) {
          printf("%d:%d ", j, knapsack9);
          sum += knapsack9;
        }
      }
      printf("sum %d\n", sum);
    }

    // Feasibility Check
    if (w > MAXWEIGHT) {
      klee_assert(p <= 999999);
      return 0;
    }
  }
  klee_assert(p <= BOUND);
}

