#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <klee/klee.h>

#define N 50
#define BOUND 0
#define MAXRAND 5 //1001

//#define  DEBUG 1
#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT
#endif

int graph[N + 1][N + 1] = {0}; 
/*{ 
  { 0,0,   0,   0,   0,   0},
  { 0,0,   2,   5,   4,8888},
  { 0,0,   0,   6,   2,   5},
  { 0,0,   0,   0,   1,   4},
  { 0,0,   0,   0,   0,   2},
  { 0,0,   0,   0,   0,   0}
};*/

int node = 1;
int distance = 0;




void print() {

	for (int i = 1; i <= N; i++) {
		DEBUG_PRINT("Node %2d: edges: ", i);
		for (int j = 1; j <= N; j++)
			DEBUG_PRINT("%5d", graph[i][j]);
		DEBUG_PRINT("\n");
	}
	DEBUG_PRINT("=========================================================================\n");
}

void init() {
	srand(12345);
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			graph[i][j] = 1 + (rand() % (MAXRAND + 1));
		}
	}
	graph[1][N] = 8888;

}

int choice()
{
   for (int j = node + 1; j < N; j++) {
   	int c;
 	klee_make_symbolic(&c, sizeof(c), "c");
	if (c>0) {
		DEBUG_PRINT("Choice: %5d\n", j);
		return j;
	}
   }
   DEBUG_PRINT("Last: %5d\n", N);
   return N;
}

int main() {
    init();
    print();
    while(node != N){
	int b;
	int i = choice();
	distance = distance + graph[node][i];
	node = i; 
    }  
    printf("Distance:%5d\n", distance);
    //__CPROVER_assert( distance >= BOUND , "Assertion Unsuccessful!");
    klee_assert( distance >= BOUND);
    return 0;
}

