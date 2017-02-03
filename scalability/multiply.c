/**
 * multiply.c - A KLEE example adapted from the paper
 * Hansen, Schachte, Sondergaard: State Joining and Splitting for the
 * Symbolic Execution of Binaries
 *
 * There are 2^64 paths through the function multiply. Simple path
 * enumeration without state merging would enumerate all paths.
 */

#include <stdint.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define even(x) ((x) & 1)

uint64_t multiply(uint64_t x0, uint64_t y0);


int main() {
  uint64_t x0, y0;

#ifdef LLBMC
  x0 = __llbmc_nondef_uint64_t();
  y0 = __llbmc_nondef_uint64_t();
#else
  klee_make_symbolic(&x0, sizeof(x0), "x0");
  klee_make_symbolic(&y0, sizeof(y0), "y0");
#endif

  return multiply(x0, y0);
}

uint64_t multiply(uint64_t x0, uint64_t y0) {
  uint64_t x = x0, y = y0, z = 0;

#ifdef LLBMC
  z = __llbmc_nondef_uint64_t();
#else
  klee_make_symbolic(&z, sizeof(z), "z");
#endif

  while (x != 0) {
    if (!even(x)) {
      z += y;
    }
    x = x >> 1;
    y = y << 1;
  }

  return z;
}

