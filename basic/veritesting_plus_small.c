/*
 * From Avgerinos et al.: Enhancing Symbolic Execution with
 * Veritesting, with modifications proposed by Chu Duc Hiep.
 *
 * In this example, Tracer-X KLEE over-subsumes and not able to
 * demonstrate the assertion violation, which can be demonstrated by
 * LLBMC. In this version, the variable start is also replaced with 0,
 * and the loop iterations reduced to 9.
 *
 * To run with LLBMC, compile with -DLLBMC, and execute LLBMC with the
 * options --ignore-missing-function-bodies -function-name=main
 * -no-overflow-checks -max-loop-iterations=0
 * -max-function-call-depth=0 -counterexample.
 *
 * Portions copyright 2017 National University of Singapore
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main(int argc, char **argv) {
  int counter;
  char input[9];

#ifdef LLBMC
  for (int i = 0; i < 9; ++i) {
    input[i] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(input, 9 * sizeof(char), "input");
#endif

  counter = 0;

  for (int i = 0; i < 9; i++) {
    if (input[i] == 'B') {
      counter++;
    } else {
      counter += i;
    }
  }

// 37 is the maximum value for counter
#ifdef LLBMC
  __llbmc_assert(counter != 37);
#else
  klee_assert(counter != 37);
#endif

  return 0;
}
