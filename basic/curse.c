/*
 * Copyright 2017 National University of Singapore
 *
 * This program consists of two sections: The first section constrains
 * the characters on the string b, and the second section branches
 * based on the values in b. This shows that even with interpolation,
 * no subsumption can be gained.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main(int argc, char **argv) {
  char b[3];
  int x = 0;

#ifdef LLBMC
  for (int i = 0; i < 3; ++i)
    b[i] = __llbmc_nondef_char();
#else
  klee_make_symbolic(b, 3 * sizeof(char), "b");
#endif

  /* Constrain the characters on b */
  if (b[0]) x += 1; else x += 2;
  if (b[1]) x += 3; else x += 4;
  if (b[2]) x += 5; else x += 6;

  /* Create infeasible branches */
  if (b[0]) x += 7; else x += 8;
  if (b[1]) x += 9; else x += 10;
  if (b[2]) x += 11; else x += 12;

  return 0;
}
