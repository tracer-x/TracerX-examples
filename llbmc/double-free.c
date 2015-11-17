#include <stdlib.h>
#include <assert.h>
#include <klee/klee.h>

struct S {
    int x;
    struct S *n;
};

int main(int argc, char *argv[]) {
    struct S *p, *q;

    klee_make_symbolic(&p, sizeof(p), "p");
    klee_make_symbolic(&q, sizeof(q), "q");

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

    assert(p->x + q->x == 10);

    free(q);
    free(p); // a double-free can occur here

    return 0;
}
