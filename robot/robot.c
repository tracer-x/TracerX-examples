/*
 * Copyright 2020 National University of Singapore
 *
 */

#include <klee/klee.h>
#include <stdlib.h>

#define N 10
#define INF 9999999
#define QUALITY_BOUND 120
#define RESOURCE_BOUND 50

int posx = 0;
int posy = 0;

int grid[N][N] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 0, 2, 3, 4, 5, 6, 7, 8, 9},
    {2, 2, 0, 3, 4, 5, 6, 7, 8, 9},
    {3, 3, 3, 0, 4, 5, 6, 7, 8, 9},
    {4, 4, 4, 4, 0, 5, 6, 7, 8, 9},
    {5, 5, 5, 5, 5, 0, 6, 7, 8, 9},
    {6, 6, 6, 6, 6, 6, 0, 7, 8, 9},
    {7, 7, 7, 7, 7, 7, 7, 0, 8, 9},
    {8, 8, 8, 8, 8, 8, 8, 8, 0, 9},
    {9, 9, 9, 9, 9, 9, 9, 9, 9, 0}

};

int quality[N][N] = {
    {1, 2, 3, 4, 5, 6,7,8,9,10},
    {10,9,8,7,6, 5, 4, 3, 2, 1},
    {1, 2, 3, 4, 5, 6,7,8,9,10},
    {10,9,8,7,6, 5, 4, 3, 2, 1},
    {1, 2, 3, 4, 5, 6,7,8,9,10},
    {10,9,8,7,6, 5, 4, 3, 2, 1},
    {1, 2, 3, 4, 5, 6,7,8,9,10},
    {10,9,8,7,6, 5, 4, 3, 2, 1},
    {1, 2, 3, 4, 5, 6,7,8,9,10},
    {10,9,8,7,6, 5, 4, 3, 2, 1}
};


int conflicts[4][4] = {
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0},
   { 0, 0 , 0 ,0, 0, 0, 0, 0, 0, 0}
};


int conflict(int *decisions, int count) {
  for(int i=0; i<count-2;i++ )
     if(conflicts[count-1][i] == 1)
        return 1;
  return 0;
}


char choice() {
	char b; klee_make_symbolic(&b, sizeof(char), "b");
	return b;
	
}

void action(int i) {
	switch (i) {
		case 0: posx++; break;
		case 1: posy++; break;
		default: exit(1);
	}
}

int unreachable(posx, posy) {
	if (posx < 0 || posx >= N) return 1;
	if (posy < 0 || posy >= N) return 1;
	if (grid[posx][posy] >= INF) return 1;
	return 0;
}

main() {
	int a, w, i = 0;
	char direction[] = "01";
	int current_r = 0, current_q = 0;
	
	while(1){
		if (posx == N-1 && posy == N-1)  goto FEASIBLE;
		i++;
		action(choice());
		//printf("posx, posy:%d,%d\n ",posx, posy);
		if (unreachable(posx, posy))  goto INFEASIBLE;
		int r = grid[posx][posy];
		//printf("current_r + r:%d,%d\n ",current_r , r);
		if (current_r + r > RESOURCE_BOUND) goto INFEASIBLE;
		current_r += r;
		int q = quality[posx][posy];
		current_q += q;
	//	*** record conflict types ****/
	}  

FEASIBLE: printf("resource:%d, ",current_r);
	  printf("quality:%d\n",current_q);
	  klee_assert(current_q <= QUALITY_BOUND);
INFEASIBLE:
	  //printf("Infeasible: resource:%d, ",current_r);
	  //printf("quality:%d\n",current_q);
	  return 0;
}

/***

CLP

infeasible(A, I, Pushback) :- I > 0, conflict(A[I], Pushback).
infeasible(A, I, Pushback) :- I > 0, infeasible(A, I-1, Pushback).

***/
