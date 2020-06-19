#include <stdio.h>
#include <klee/klee.h>

int main(int argc, char **argv) {

  int a,b,count = 0;
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");  
  int x = a, y = b;
  while (1) {
    int c;
    klee_make_symbolic(&c, sizeof(int), "c");
    if (c % 2) { x+=2;  y ++; } else { x++;  y += 2; }
    if (++count > 3) break;
  }
  
  
  klee_assert(x + y -a - b < 301);

  return 0;
}
