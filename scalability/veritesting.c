/*
 * From Avgerinos et al.: Enhancing Symbolic Execution with
 * Veritesting
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main(int argc, char **argv)
{
  int counter = 0;
  char input[100];
  
#ifdef LLBMC
  for (int i = 0; i < 100; ++i) {
    input[i] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(input, 100 * sizeof(char), "input");
#endif
  
  for (int i = 0; i < 100; i++) {
      if (input[i] == 'B') {
          counter++;
      }
  }

#ifdef LLBMC
  __llbmc_assert(counter != 75);
#else
  klee_assert(counter != 75);
#endif
  
  return 0;
}
