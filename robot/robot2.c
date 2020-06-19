/*
 * Copyright 2020 National University of Singapore
 *
 */

#include <klee/klee.h>
#include <stdlib.h>

#define N 3
#define INF 9999999
#define QUALITY_BOUND 15
#define RESOURCE_BOUND 6

int posx = 0;
int posy = 0;
int conflict = 0;

int grid[N][N] = {{0, 1, 3}, {1, 0, 2}, {2, 2, 1}};

int quality[N][N] = {{0, 3, 8}, {4, 5, 3}, {7, 5, 1}};

int type[N][N] = {{1, 4, 1}, {2, 1, 8}, {1, 2, 1}};

void storeType() {
  int mask = 2 ^ type[posx][posy];
  conflict = conflict | mask;
}

int hasConflict() {
  int mask1 = 2; // T1
  int mask2 = 8; // T3

  int mask3 = 4; // T2
  int mask4 = 8; // T3
  if ((conflict & mask1) > 0 && (conflict & mask2) > 0)
    return 1;
  if ((conflict & mask3) > 0 && (conflict & mask4) > 0)
    return 1;
  return 0;
}

char choice() {
  char b;
  klee_make_symbolic(&b, sizeof(char), "b");
  return b;
}

void action(int i) {
  switch (i) {
  case 0:
    posx++;
    break;
  case 1:
    posy++;
    break;
  default:
    exit(1);
  }
}

int unreachable(posx, posy) {
  if (posx < 0 || posx >= N)
    return 1;
  if (posy < 0 || posy >= N)
    return 1;
  if (grid[posx][posy] >= INF)
    return 1;
  return 0;
}

main() {
  int current_r = 0, current_q = 0;

  while (1) {
    if (posx == N - 1 && posy == N - 1)
      goto FEASIBLE;
    action(choice());

    if (unreachable(posx, posy))
      goto INFEASIBLE;
    int r = grid[posx][posy];

    if (current_r + r > RESOURCE_BOUND)
      goto INFEASIBLE;

    storeType();
    if (hasConflict())
      goto INFEASIBLE;

    current_r += r;
    int q = quality[posx][posy];
    current_q += q;
    printf("posx:%d,posy:%d,current_q:%d,current_r:%d,conflict:%d\n", posx,
           posy, current_q, current_r, conflict);
    // tracerx_memo_check(4,posx,posy,current_q,current_r);
    // tracerx_memo(4,posx,posy,current_q,current_r);
  }

FEASIBLE:
  printf("resource:%d, ", current_r);
  printf("quality:%d\n", current_q);
  klee_assert(current_q <= QUALITY_BOUND);
INFEASIBLE:
  klee_assert(conflict <= 99);
  klee_assert(current_r <= 99);

  return 0;
}
