/*
 * Copyright 2017 National University of Singapore
 *
 */
#include <stdio.h>
#include <klee/klee.h>

int main() {

    char b1,b2,b3;

    int x = 0;
    int y = 0,z=0, w=1;

    klee_make_symbolic(&b1, sizeof(char), "b1");
    klee_make_symbolic(&b2, sizeof(char), "b2");
    klee_make_symbolic(&b3, sizeof(char), "b3");

    if (b1 > 0) x = x + 3; else x = x + 0;
    if (b2 > 0) x = x + 6; else x = x + 0;
    if (b3 > 0) x = x + 9; else x = x + 0;
   
    return 0;
}
