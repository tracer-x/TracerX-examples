/**
 * wegner.c - A KLEE example adapted from the paper
 * Hansen, Schachte, Sondergaard: State Joining and Splitting for the
 * Symbolic Execution of Binaries
 *
 * This example counts the number of 1-bits in a symbolic 64-bit number.
 * The example has 65 paths. KLEE could not figure this out.
 */

#include <stdint.h>
#include <klee/klee.h>

uint64_t popCount (uint64_t y);

int main() {
  uint64_t y;
  klee_make_symbolic(&y, sizeof(y), "y");
  return popCount(y);
}

uint64_t popCount (uint64_t y) {
  uint64_t c;

  for (c = 0; y; c++)
    y &= y - 1;

  return c;
}
