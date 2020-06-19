#include <klee/klee.h>

int wcet;
int UB = 100;
int B = 100;
int LB = 0;

// int UB = 35;
// int B = 35;
// int LB = 34;

int main() {
  wcet = 0;
  unsigned int a[25];
  int temp;
  klee_make_symbolic(a, 25 * sizeof(int), "a");
  int i, j;
  i = 0;
  int b1, b2, b3, b4, b5, b6, b7, b8;
  klee_make_symbolic(&b1, sizeof(int), "b1");
  klee_make_symbolic(&b2, sizeof(int), "b2");
  klee_make_symbolic(&b3, sizeof(int), "b3");
  klee_make_symbolic(&b4, sizeof(int), "b4");
  klee_make_symbolic(&b5, sizeof(int), "b5");
  klee_make_symbolic(&b6, sizeof(int), "b6");
  klee_make_symbolic(&b7, sizeof(int), "b7");
  klee_make_symbolic(&b8, sizeof(int), "b8");

  int v1, v2;
  klee_make_symbolic(&v1, sizeof(int), "v1");
  klee_make_symbolic(&v2, sizeof(int), "v2");
  if (b1 > 0)
    a[0] = v1;
  else
    a[0] = v2;
  if (b2 > 0)
    a[1] = v1;
  else
    a[1] = v2;
  if (b3 > 0)
    a[2] = v1;
  else
    a[2] = v2;
  if (b4 > 0)
    a[3] = v1;
  else
    a[3] = v2;
  if (b5 > 0)
    a[4] = v1;
  else
    a[4] = v2;
  if (b6 > 0)
    a[5] = v1;
  else
    a[5] = v2;
  if (b7 > 0)
    a[6] = v1;
  else
    a[6] = v2;
  if (b1 > 0)
    a[7] = v1;
  else
    a[7] = v2;

  i = 2;
  while (i < 8) {
    j = i;
    while (j > 0 && a[j] < a[j - 1]) {
      temp = a[j];
      a[j] = a[j - 1];
      a[j - 1] = temp;
      j--;
    }
    i++;
  }
  tracerx_check();

  return 1;
}
