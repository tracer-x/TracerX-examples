/* KLEE adaptation of double-free.c in LLBMC 2013.1
 *
 * Portions Copyright 2016, 2017 National University of Singapore
 *
 * See also LLBMC copyright and license in license/LLBMC_LICENSE.
 */

#include <stdlib.h>

#ifdef LLBMC
#include <llbmc.h>
#else
#include <assert.h>
#include <klee/klee.h>
#endif

struct S {
    int x;
    struct S *n;
};

int main(int argc, char *argv[]) {
    struct S *p, *q;

#ifdef LLBMC
  p = __llbmc_nondef_uint64_t();
  q = __llbmc_nondef_uint64_t();
#else
    klee_make_symbolic(&p, sizeof(p), "p");
    klee_make_symbolic(&q, sizeof(q), "q");
#endif

    p = malloc(sizeof(struct S));
    p->x = 5;
    p->n = NULL;

    if (argc > 1) {
        q = malloc(sizeof(struct S));
        q->x = 5;
        q->n = p;
    } else {
        q = p;
    }

#ifdef LLBMC
  __llbmc_assert(p->x + q->x == 10);
#else
  klee_assert(p->x + q->x == 10);
#endif

    free(q);
    free(p); // a double-free can occur here

    return 0;
}
