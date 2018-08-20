#include <klee/klee.h>
#include <stdio.h>
#include <stdlib.h>

#define BOUND 10
#define MAXWEIGHT 10

int knapsack0, knapsack1, knapsack2, knapsack3, knapsack4, knapsack5, knapsack6, knapsack7, knapsack8, knapsack9;


int main() {
  int i, j, exp = 1, sum = 0, w = 0, p = 0;

  for (i = 0; i < 10; i++) {
    exp = 1;
    int choice;
    klee_make_symbolic(&choice, sizeof(int), "choice");
    if (choice > 0) {
      w += exp;
      p += exp;
      if (i==0) {
        knapsack0 = exp;
      } else if(i==1) {
        knapsack1 = exp;
      } else if(i==2) {
        knapsack2 = exp;
      } else if(i==3) {
        knapsack3 = exp;
      } else if(i==4) {
        knapsack4 = exp;
      } else if(i==5) {
        knapsack5 = exp;
      } else if(i==6) {
        knapsack6 = exp;
      } else if(i==7) {
        knapsack7 = exp;
      } else if(i==8) {
        knapsack8 = exp;
      } else if(i==9) {
        knapsack9 = exp;
      }
    }
  }
  klee_assert(w <= BOUND);
}

