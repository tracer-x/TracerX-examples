#define A_MAX 3

int a[A_MAX];

void foo(int m)
{
  int i;

  for (i = 0; i < m; i++)
    a[i] = i;  // memory access violation, if m > A_MAX = 3
}
