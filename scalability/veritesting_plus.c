/*
 * From Avgerinos et al.: Enhancing Symbolic Execution with
 * Veritesting, with modifications proposed by Chu Duc Hiep.
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
  int counter, start;
  char input[100];
  
#ifdef LLBMC
  for (int i = 0; i < 100; ++i) {
    input[i] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(input, 100 * sizeof(char), "input");
#endif

  counter = start;
  
  for (int i = 0; i < 100; i++) {
      if (input[i] == 'B') {
	counter++;
      } else {
	counter += i;
      }
  }

#ifdef LLBMC
  __llbmc_assert(counter != start + 501);
#else
  klee_assert(counter != start + 501);
#endif
  
  return 0;
}
