
/*
 * Copyright 2017 National University of Singapore
 *
 */
#include<klee/klee.h>
int main() {

    char b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11,b12,b13,b14,b15,b16,b17,b18,b19,b20,b21,b22,b23,b24,b25,b26,b27,b28,b29,b30,b31,b32,b33,b34,b35,b36,b37,b38,b39,b40,b41,b42,b43,b44,b45,b46,b47,b48,b49,b50,b51,b52,b53,b54,b55,b56,b57,b58,b59,b60,b61,b62,b63,b64,b65,b66,b67,b68,b69,b70,b71,b72,b73,b74,b75,b76,b77,b78,b79,b80,b81,b82,b83,b84,b85,b86,b87,b88,b89,b90,b91,b92,b93,b94,b95,b96,b97,b98,b99;

    int x = 0;

    klee_make_symbolic(&b0, sizeof(char), "b0");    
    klee_make_symbolic(&b1, sizeof(char), "b1");
    klee_make_symbolic(&b2, sizeof(char), "b2");    
    klee_make_symbolic(&b3, sizeof(char), "b3");
    klee_make_symbolic(&b4, sizeof(char), "b4");    
    klee_make_symbolic(&b5, sizeof(char), "b5");
    klee_make_symbolic(&b6, sizeof(char), "b6");    
    klee_make_symbolic(&b7, sizeof(char), "b7");
    klee_make_symbolic(&b8, sizeof(char), "b8");    
    klee_make_symbolic(&b9, sizeof(char), "b9");
    klee_make_symbolic(&b10, sizeof(char), "b10");    
    klee_make_symbolic(&b11, sizeof(char), "b11");
    klee_make_symbolic(&b12, sizeof(char), "b12");    
    klee_make_symbolic(&b13, sizeof(char), "b13");
    klee_make_symbolic(&b14, sizeof(char), "b14");    
    klee_make_symbolic(&b15, sizeof(char), "b15");
    klee_make_symbolic(&b16, sizeof(char), "b16");    
    klee_make_symbolic(&b17, sizeof(char), "b17");
    klee_make_symbolic(&b18, sizeof(char), "b18");    
    klee_make_symbolic(&b19, sizeof(char), "b19");    


    if (b2 > 0) x = x + 6; else x = x + 0;
    if (b3 > 0) x = x + 9; else x = x + 0;
    if (b4 > 0) x = x + 12; else x = x + 0;
    if (b5 > 0) x = x + 15; else x = x + 0;
    if (b6 > 0) x = x + 18; else x = x + 0;
    if (b7 > 0) x = x + 21; else x = x + 0;
    if (b8 > 0) x = x + 24; else x = x + 0;
    if (b9 > 0) x = x + 27; else x = x + 0;
    if (b10 > 0) x = x + 30; else x = x + 0;
    if (b11 > 0) x = x + 33; else x = x + 0;
    if (b12 > 0) x = x + 36; else x = x + 0;
    if (b13 > 0) x = x + 39; else x = x + 0;
    if (b14 > 0) x = x + 42; else x = x + 0;
    if (b15 > 0) x = x + 45; else x = x + 0;
    if (b16 > 0) x = x + 48; else x = x + 0;
    if (b17 > 0) x = x + 51; else x = x + 0;
    if (b18 > 0) x = x + 54; else x = x + 0;
    if (b19 > 0) x = x + 57; else x = x + 0;

    int BOUND = 150;
    klee_assert( (BOUND != x));
    return 0;
}
