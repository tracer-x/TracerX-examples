/*
 * Copyright 2017 National University of Singapore
 *
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main(int argc, char **argv) {
  char b[10];
  int x = 0;

#ifdef LLBMC
  for (int i = 0; i < 10; ++i)
    b[i] = __llbmc_nondef_char();
#else
  klee_make_symbolic(b, 10 * sizeof(char), "b");
#endif

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
  if (b[3] > 0)
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

  klee_assert(x != 990);

  return 0;
}
