/* Subsumption should fail and error reported on the local variable l
 * In reference to the file DP-global.c
 *
 * Copyright 2020 National University of Singapore
 *
 */
 
#include <klee/klee.h>
int main() {
    int c,d;
    int l = 0;
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


