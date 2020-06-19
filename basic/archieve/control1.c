#include <stdio.h>
#include <klee/klee.h>
int main(int argc, char **argv) {

  int count = 0, x = 0, y = 0;
  int c[100];
  klee_make_symbolic(c, 100*sizeof(int), "c");
  if (c[0]) { x++;  y += 2; } else { y++;  x += 2; }
  if (c[1]) { x++;  y += 2; } else { y++;  x += 2; }  
  if (c[2]) { x++;  y += 2; } else { y++;  x += 2; }    

  
  klee_assert(x + y < 301);

  return 0;
}
