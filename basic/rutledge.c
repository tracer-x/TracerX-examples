/*
 * An example posted by Rick Rutledge in klee-dev mailing list. This
 * example generates 102 paths with DFS and Z3 due to symbolic offset.
 * It triggered an assertion failure in Tracer-X code.
 *
 * http://mailman.ic.ac.uk/pipermail/klee-dev/2016-November/001476.html
 */

#include <klee/klee.h>

#define MAXSTR 10

int test(char *str, int offset) {

  if (str[offset] == '\n') {
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {

  char str[MAXSTR];
  int offset;

  klee_make_symbolic(str, MAXSTR, "str");
  offset = klee_int("offset");

  /* With the following two assumes, only two paths are traversed. */
  
  /* klee_assume(offset >= 0); */
  /* klee_assume(offset < MAXSTR); */

  int result = test(str, offset);

  return result;
}
