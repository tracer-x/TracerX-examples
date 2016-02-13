/*
 * Copyright 2015 National University of Singapore 
 */
#include <klee/klee.h>
#include <assert.h>

int main() {
  int p1,p2, p3, x;
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&x, sizeof(x), "x");

  klee_assume (x <= 0);

  if (p1 > 8)
    x = x + 1; 

  if (p2 > 8)
    x = x;
  else
    x = x + 2;
 
  if (p3 > 8)
    x = x + 3;
	  
  assert (x <= 5);

  return x;
} 
