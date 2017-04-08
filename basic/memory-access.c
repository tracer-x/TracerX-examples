/* KLEE adaptation of memory-access.c in LLBMC 2013.1
 * Portions Copyright 2016, 2017 National University of Singapore
 *
 * See also LLBMC copyright and license in license/LLBMC_LICENSE.
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

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

#ifdef LLBMC
  m = __llbmc_nondef_int();
#else
  klee_make_symbolic(&m, sizeof(m), "m");
#endif

  foo(m);
}
