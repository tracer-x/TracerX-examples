/* Subsumption should fail and error reported on the global variable l
 *
 * Copyright 2020 National University of Singapore
 *
 */

#include <klee/klee.h>
int l = 0;
int main() {
    int c,d;
    klee_make_symbolic(&c, sizeof(int), "c");
    if (c == 0) {
        if (!l) {
            l = 1; 
        }
    } else if(c == 1) {
        if (l) {
            klee_assert(0);
        }
    }
    klee_make_symbolic(&d, sizeof(int), "d");
    if (d == 0) {
        if (!l) {
            l = 1; 
        }
    } else if(d == 1) {
        if (l) {
            klee_assert(0);
        }
    }
    return 0;
}


