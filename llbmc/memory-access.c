#include <klee/klee.h>

#define A_MAX 3

int a[A_MAX];

void foo(int m)
{
  int i;

  for (i = 0; i < m; i++)
    a[i] = i;  // memory access violation, if m > A_MAX = 3
}

int main() {
  int m;

  klee_make_symbolic(&m, sizeof(m), "m");
  foo(m);
}
