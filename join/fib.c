/*
 * Fibonacci function
 *
 * Copyright 2016 National University of Singapore
 */

#include <klee/klee.h>
#include <assert.h>

int main() {
  unsigned n;
  int f1=0, f2=1, f;
  
  klee_make_symbolic(&n, sizeof(n), "n");
  klee_assume(n <= 20);
  klee_assume(n >= 1);
  
  do {
    
    f=f1+f2;
    f1=f2;
    f2=f;

    // klee_join("fib", n, f);

    n--;
  } while (n>1);
  
  return f;
}
