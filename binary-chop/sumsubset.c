#include <klee/klee.h>

int main(int argc, char **argv) {
  char b[10];
  int x = 0;

  klee_make_symbolic(b, 10 * sizeof(char), "b");

  if (b[0] > 0)
    x += 1;
  else
    x += 2;
  if (b[1] > 0)
    x += 3;
  else
    x += 4;
  if (b[2] > 0)
    x += 5;
  else
    x += 6;
  if (b[3] > 0)
    x += 7;
  else
    x += 8;
  if (b[4] > 0)
    x += 9;
  else
    x += 10;
  if (b[5] > 0)
    x += 11;
  else
    x += 12;
  if (b[6] > 0)
    x += 13;
  else
    x += 14;
  if (b[7] > 0)
    x += 15;
  else
    x += 16;
  if (b[8] > 0)
    x += 17;
  else
    x += 18;
  if (b[9] > 0)
    x += 19;
  else
    x += 20;
    
  if(x>99)
    klee_assert(x > 99);
  else
    klee_assert(x < 99);

  return 0;
}
