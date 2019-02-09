#include <klee/klee.h>
#include <stdlib.h>

#define N 10
#define CONF 4
#define INF 9999999
#define QUALITY_BOUND 118
#define RESOURCE_BOUND 50

struct cell {
   int posx;
   int posy;
};

struct conflict {
   struct cell item1;
   struct cell item2;
};


int posx = 0;
int posy = 0;
struct cell decisions[1000];

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


struct conflict conflicts[CONF] = {
   {{ 1 , 1}, { 1 , 2} },
   {{ 3 , 4}, { 5 , 7} },
   {{ 4 , 6}, { 8 , 9} },
   {{ 1 , 2}, { 5 , 8} }
};


int hasConflicts(struct cell *decisions, int count) {
  for(int i=0; i<CONF;i++ ){
     struct conflict c = conflicts[i];
     struct cell i1 = c.item1;
     struct cell i2 = c.item2;
     struct cell confItem;
     if(decisions[count].posx == i1.posx && 
        decisions[count].posy == i1.posy){
        confItem = i2;
     }else if (decisions[count].posx == i2.posx && 
               decisions[count].posy == i2.posy){
        confItem = i1;        
     } else
     	continue;
     for(int j=0; j<count-1;j++ )
        if(decisions[j].posx == confItem.posx && 
           decisions[j].posy == confItem.posy)
           return 1;
  }
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
		action(choice());

		if (unreachable(posx, posy))  goto INFEASIBLE;
		int r = grid[posx][posy];

		if (current_r + r > RESOURCE_BOUND) goto INFEASIBLE;

		struct cell newCell = {posx,posy};
		decisions[i]= newCell;
		if (hasConflicts(decisions,i)) goto INFEASIBLE;
	
		current_r += r;
		int q = quality[posx][posy];
		current_q += q;
		//printf("posx,posy:%d,%d,%d,%d\n",posx,posy,current_q,current_r);
		tracerx_memo_check(4,posx,posy,current_q,current_r);
		tracerx_memo(4,posx,posy,current_q,current_r);
		i++;
	}  

FEASIBLE: printf("resource:%d, ",current_r);
	  printf("quality:%d\n",current_q);
	  klee_assert(current_q <= QUALITY_BOUND);
INFEASIBLE:

	  return 0;
}

