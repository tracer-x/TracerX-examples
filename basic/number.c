/**
 * number.c - A KLEE example adapted from the paper
 * Hansen, Schachte, Sondergaard: State Joining and Splitting for the
 * Symbolic Execution of Binaries
 *
 * A somewhat classical example that shows the advantage of symbolic execution
 * over black-box test generation. It is unlikely that a black-box random test
 * approach would be able to figure out that failure is possible.
 */

#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

int main() {
  char s[9];
  long number;

  printf("Enter a number:");
  fgets(s, sizeof(s), stdin);
  number = atol(s);

  // We symbolicize the number at this point to
  // make exploration possible.
  klee_make_symbolic(&number, sizeof(number), "number");

  if (number == 12345678) {
    assert(0);
  }

  return 0;
}
