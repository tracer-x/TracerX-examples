/*
 * Example with malloc from KLEE's test suite.
 * Originally named
 * 2007-08-06-access-after-free.c
 *
 * KLEE's license applies. See 
 * https://github.com/klee/klee/blob/master/LICENSE.TXT
 */

#include <klee/klee.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  int a;
  unsigned char *p = malloc(4);

  klee_make_symbolic(&a, sizeof a, "a");
  klee_make_symbolic(p, sizeof p, "p");

  p[0] |= 16;

  if (a) {
    free(p);

    // this should give an error instead of
    // pulling the state from the parent, where
    // it is not free
    assert(p[0] > 10);
   
    return 0;
  }
  
  assert(p[0] > 10);

  return 0;
}
