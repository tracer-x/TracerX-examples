/**
 * wegner.c - A KLEE example adapted from the paper
 * Hansen, Schachte, Sondergaard: State Joining and Splitting for the
 * Symbolic Execution of Binaries
 *
 * This example counts the number of 1-bits in a symbolic 64-bit number.
 * The example has 65 paths.
 */

#include <stdint.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

uint64_t popCount (uint64_t y);

int main() {
  uint64_t y;
#ifdef LLBMC
  y = __llbmc_nondef_uint64_t();
#else
  klee_make_symbolic(&y, sizeof(y), "y");
#endif
  return popCount(y);
}

uint64_t popCount (uint64_t y) {
  uint64_t c;

  for (c = 0; y; c++)
    y &= y - 1;

  return c;
}
