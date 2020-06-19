#include <stdio.h>
#include <klee/klee.h>

int main(int argc, char **argv) {

  int a,b,count = 0;
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");  
  int  x = a, y = b;

  while (1) {
    int c;
    klee_make_symbolic(&c, sizeof(int), "c");
    if (c % 2) { x+=2; } else { x = x + b + 1; x = x + 0; x = x - b;}
    if (++count > 5) break;
  }
  
  
  klee_assert(x -a < 83);

  return 0;
}
