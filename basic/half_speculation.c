/*
Copyright 2020 National University of Singapore
Execute:  make memo_check.tx

Checking the functionality of the special functions tracerx_half_speculation.

These functions implement memo operation. 
*/

#include <klee/klee.h>

int main() {
  int x;
  klee_make_symbolic(&x, sizeof(x), "x");
  
  if (x < 0){
      tracerx_half_speculation(1);
  } else {
      tracerx_half_speculation(0);
  }
  printf("We reached here.\n");
} 
