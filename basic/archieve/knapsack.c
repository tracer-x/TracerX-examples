#include <stdio.h>
#include <klee/klee.h>
#include <stdlib.h>

#define MAXCHOICE 100
#define MAXWEIGHT 483
#define N 10
#define BOUND 483

int choice[MAXCHOICE], *choice_ptr;

int knapsack[N] = {0};

int main () {

    klee_make_symbolic(choice, sizeof(choice), "choice");
    choice_ptr = choice;
    int i, j, exp = 1, sum = 0, w = 0, p = 0;

    // for (i = 0; i < N; i++) knapsack[i] = 0;

    for (i = 0; i < N; i++) {
        exp = 10;
        if (*(++choice_ptr)) {
            w += exp;
            p += exp;
            knapsack[i] = exp;
        }
        // Feasibility Check
        if (i == N-1) {
            for (j = 0; j <= i; j++) { printf("%d:%d ", j, knapsack[j]); sum += knapsack[j]; }
            printf("sum %d\n", sum);
        }
        
        //if (w > MAXWEIGHT) { klee_assert(p <= 999999); return 0; }
    }
    klee_assert(p <= BOUND);
    // klee_assert(p <= BOUND - 1);
}

