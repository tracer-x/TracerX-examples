#include <klee/klee.h>
#include <stdlib.h>

#define N 5

int grid[N][N] = {{0, 1, 2, 3, 4},
                  {0, 0, 2, 3, 4},
                  {0, 0, 0, 3, 4},
                  {0, 0, 0, 0, 4},
                  {0, 0, 0, 0, 0}};

int profit[N][N] = {{0, 11, 22, 33, 44},
                    {0, 0, 22, 33, 44},
                    {0, 0, 0, 33, 44},
                    {0, 0, 0, 0, 44},
                    {0, 0, 0, 0, 0}};

int x = 0, y = 0, sum = 0;

action(i) {
  switch (i) {
  case 0: {
    x++;
    break;
  }
  case 1: {
    y++;
    break;
  }
  default:
    exit(1);
  }
}

choice(int *s) {
  for (;;) {
    if (*(s + 1) == -1)
      return *s;
    // at least two choices
    char b;
    klee_make_symbolic(&b, sizeof(char), "b");
    if (b) {
      ++s;
      continue;
    } else {
      action(*s);
      break;
    }
  }
}

int main(int argc, char **argv) {
  int s[] = {0, 1, -1};
  for (;;) {
    if (x == N - 1 || !grid[x + 1][y])
      if (y == N - 1 || !grid[x][y + 1])
        break;
      else
        y++;
    else if (!grid[x][y + 1])
      x++;
    // else choice(s);
    else {
      char b;
      klee_make_symbolic(&b, sizeof(char), "b");
      if (b)
        x++;
      else
        y++;
    }
    sum += profit[x][y];
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>> (%d %d)\n", x, y);
    if (x == N - 1 && y == N - 1)
      break;
  }
}
