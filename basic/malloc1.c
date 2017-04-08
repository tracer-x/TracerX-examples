/*
 * Example with malloc from KLEE's test suite.
 * Originally named
 * 2007-08-06-access-after-free.c
 *
 * KLEE's license applies. See 
 * https://github.com/klee/klee/blob/master/LICENSE.TXT
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif
#include <stdlib.h>

int main() {
  int a;
  unsigned char *p = malloc(4);

#ifdef LLBMC
  a = __llbmc_nondef_int();
  p = __llbmc_nondef_uint64_t();
#else
  klee_make_symbolic(&a, sizeof a, "a");
  klee_make_symbolic(p, sizeof p, "p");
#endif

  p[0] |= 16;

  if (a) {
    free(p);

    // this should give an error instead of
    // pulling the state from the parent, where
    // it is not free
#ifdef LLBMC
    __llbmc_assert(p[0] > 10);
#else
    klee_assert(p[0] > 10);
#endif

    return 0;
  }

#ifdef LLBMC
  __llbmc_assert(p[0] > 10);
#else
  klee_assert(p[0] > 10);
#endif

  return 0;
}
