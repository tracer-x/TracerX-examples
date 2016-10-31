/*
 * This example caused assertion failure in Dependency.cpp.
 */

#include <klee/klee.h>

int main()
{
  char a[100];
  char b[100];
  char *p = a;
  int x = 0;
  
  klee_make_symbolic(&p, sizeof(p), "p");
  klee_make_symbolic(&x, sizeof(x), "x");

  klee_assume(x < 50);
  klee_assume(x > 20);

  char *n = p[x + 35];

  return 0;  
}
