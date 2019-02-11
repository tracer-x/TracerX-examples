#include <klee/klee.h>
#include <stdlib.h>

#define N 10
#define INF 9999999
#define QUALITY_BOUND 120
#define RESOURCE_BOUND 150

int posx = 0;
int posy = 0;
int conflict = 0;

int grid[N][N] = {
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 0, 2, 3, 4, 5, 6, 7, 8, 9},
    {2, 2, 0, INF, 4, 5, 6, 7, 8, 9},
    {3, 3, 3, 0, 4, 5, 6, 7, 8, 9},
    {4, 4, 4, 4, 0, 5, INF, 7, 8, 9},
    {5, 5, 5, 5, 5, 0, 6, 7, 8, 9},
    {6, 6, 6, 6, INF, 6, 0, 7, 8, 9},
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


int type[N][N] = {
    {0, 1, 0, 1, 2, 3, 4, 5, 1, 0},
    {1, 0, 2, 1, 3, 5, 6, 1, 2, 0},
    {1, 2, 0, 1, 4, 5, 6, 7, 2, 1},
    {1, 0, 2, 0, 4, 5, 6, 7, 1, 2},
    {0, 1, 0, 4, 0, 5, 6, 7, 2, 3},
    {1, 2, 1, 5, 5, 0, 6, 7, 1, 4},
    {2, 1, 2, 6, 6, 6, 0, 7, 2, 5},
    {2, 2, 3, 7, 7, 7, 7, 0, 1, 6},
    {1, 1, 2, 6, 7, 6, 4, 5, 2, 2},
    {0, 2, 1, 7, 6, 7, 5, 6, 1, 1}

};

void storeType() {
	int mask = 2 ^ type[posx][posy];
  	conflict = conflict | mask; 
}

int hasConflict() {
	int mask1 = 8;
  	int mask2 = 32;
  	int mask3 = 16;
  	int mask4 = 128;
	if ((conflict & mask1) > 0 && 
	    (conflict & mask2) > 0) return 1;  	
	if ((conflict & mask3) > 0 && 
	    (conflict & mask4) > 0) return 1;  	
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
	int current_r = 0, current_q = 0;
	
	while(1){
		if (posx == N-1 && posy == N-1)  goto FEASIBLE;
		action(choice());

		if (unreachable(posx, posy))  goto INFEASIBLE;
		int r = grid[posx][posy];

		if (current_r + r > RESOURCE_BOUND) goto INFEASIBLE;
		
		storeType();
		if (hasConflict()) goto INFEASIBLE;
	
		current_r += r;
		int q = quality[posx][posy];
		current_q += q;
		//tracerx_memo_check(4,posx,posy,current_q,current_r);
		//tracerx_memo(4,posx,posy,current_q,current_r);
	}  

FEASIBLE: printf("resource:%d, ",current_r);
	  printf("quality:%d\n",current_q);
	  klee_assert(current_q <= QUALITY_BOUND);
INFEASIBLE:

	  return 0;
}

