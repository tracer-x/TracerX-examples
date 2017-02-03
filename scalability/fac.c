/* Obtained from http://www.mrtc.mdh.se/projects/wcet/benchmarks.html,
 * with LLBMC and KLEE harnessing added. */

/* MDH WCET BENCHMARK SUITE */
/*
 * Changes: CS 2006/05/19: Changed loop bound from constant to variable.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int fac (int n)
{
  if (n == 0)
     return 1;
  else
     return (n * fac (n-1));
}

int main (void)
{
  int i;
  int s = 0;
  /* volatile */ int n;

  /* We replace the following with symbolic value. */
  n = 5;

#ifdef LLBMC
  n = __llbmc_nondef_int();
  __llbmc_assume(n >= 0);
  __llbmc_assume(n <= 30);
#else
  klee_make_symbolic(&n, sizeof(int), "n");
  klee_assume(n >= 0);
  klee_assume(n <= 30);
#endif

  for (i = 0;  i <= n; i++)
      s += fac (i);

  return (s);
}

