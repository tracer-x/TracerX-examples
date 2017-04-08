/* An example to study the behavior of Tracer-X/KLEE on branching due
 * to unbounded memory access. Original example by Richard Rutledge.
 * See the discussion here:
 * http://mailman.ic.ac.uk/pipermail/klee-dev/2017-January/001550.html
 */
#include <stdlib.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define BUFFER_SIZE 16

int main(int argc, char *argv[]) {

  char *buffer = malloc(BUFFER_SIZE);
  int index;

#ifdef LLBMC
  for (int i = 0; i < BUFFER_SIZE; ++i) {
    buffer[i] = __llbmc_nondef_char();
  }
  index = __llbmc_nondef_int();
#else
  klee_make_symbolic(buffer, BUFFER_SIZE, "buffer");
  klee_make_symbolic(&index, sizeof(index), "index");
#endif

  /* The following two lines were suggested by Dan Liew, which will
   * restrict the branching to only two as the access is
   * correct. Otherwise, in Executor::executeMemoryOperation, in order
   * to perform memory bounds validity check, KLEE will attempt to
   * generate a branch for each allocated memory region with the
   * pointer value validity of index for the region as the branch
   * condition (resulting in about 195 paths). This is because KLEE
   * maintains a global memory map, and the index may just happen to
   * be a validly allocated pointer in one of the regions.
   */
#ifdef LLBMC
/*
__llbmc_nondef_assume(index >= 0);
__llbmc_nondef_assume(index < BUFFER_SIZE);
*/
#else
  /* 
     klee_assume(index >= 0);
     klee_assume(index < BUFFER_SIZE);
  */
#endif

  if (buffer[index] == '\0') {
    return 1;
  }
  return 0;
}
