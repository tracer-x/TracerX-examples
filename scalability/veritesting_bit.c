/*
 * From Avgerinos et al.: Enhancing Symbolic Execution with
 * Veritesting, with modifications proposed by Joxan Jaffar.
 *
 * Portions copyright 2017 National University of Singapore
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main(int argc, char **argv)
{
  uint64_t counter = 0;
  char input[64];
  
#ifdef LLBMC
  for (int i = 0; i < 64; ++i) {
    input[i] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(input, 64 * sizeof(char), "input");
#endif
  
  for (int i = 0; i < 64; i++) {
      if (input[i] == 'B') {
	counter |= (((uint64_t) 1) << i);
      }
  }

#ifdef LLBMC
  __llbmc_assert(counter != 75);
#else
  klee_assert(counter != 75);
#endif
  
  return 0;
}
