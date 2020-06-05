/*
Copyright 2020 National University of Singapore
Execute:  make memo_check.tx

Checking the functionality of the special functions tracerx_memo_check and
tracerx_memo.

These functions implement memo operation. 
*/

#include <klee/klee.h>

int main() {
  int x;
  klee_make_symbolic(&x, sizeof(x), "x");
  
  if (x < 0){
     x = -x;
     
  }
  tracerx_memo_check(5,1,2,3,4,5);
  tracerx_memo(5,1,2,3,4,5);
  printf("We reached here.\n");
} 
