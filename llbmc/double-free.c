#include <stdlib.h>
#include "llbmc.h"

struct S {
    int x;
    struct S *n;
};

int main(int argc, char *argv[]) {
    struct S *p, *q;

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

    __llbmc_assert(p->x + q->x == 10);

    free(q);
    free(p); // a double-free can occur here

    return 0;
}
