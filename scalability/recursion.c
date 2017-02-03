/* Obtained from http://www.mrtc.mdh.se/projects/wcet/benchmarks.html,
 * with LLBMC and KLEE harnessing added */

/* $Id: recursion.c,v 1.2 2005/04/04 11:34:58 csg Exp $ */

/* Generate an example of recursive code, to see  *
 * how it can be modeled in the scope graph.      */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

/* self-recursion  */
int fib(int i)
{
  if(i==0)
    return 1;
  if(i==1)
    return 1;
  return fib(i-1) + fib(i-2);
}

/* mutual recursion */
int anka(int);

int kalle(int i)
{
  if(i<=0)
    return 0;
  else
    return anka(i-1);
}

int anka(int i)
{
  if(i<=0)
    return 1;
  else
    return kalle(i-1);
}

/* extern volatile */ int In;

int main(void)
{
  int a;

#ifdef LLBMC
  a = __llbmc_nondef_int();
  __llbmc_assume(a >= 0);
  __llbmc_assume(a <= 10);
#else
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_assume(a >= 0);
  klee_assume(a <= 10);
#endif

  In = fib(a);
  return 0;
}
