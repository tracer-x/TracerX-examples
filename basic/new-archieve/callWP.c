#include <stdio.h>
#include <klee/klee.h>

int f(int z) {

  int a;
  klee_make_symbolic(&a, sizeof(int), "a");
  if(a > 0) {
    z += 1;
  } else {
    z += 2;
  }
  return z;

}
int main() {

  int x = 5;
  int a;
  klee_make_symbolic(&a, sizeof(int), "a");
  if(a > 0) {
    x += 1;
  } else {
    x += 2;
  }
  
  int y = f(x);
  
  klee_assert(y > 5);
  return 0;

}
