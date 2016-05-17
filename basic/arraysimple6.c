/*
 * Subsumption test with symbolic index. This exposed the issue that
 * some memory allocations are not stored as interpolant.
 *
 * A simplified version of regexp_nonrecursive2.c.
 */
#include <klee/klee.h>

static int matchhere(char *re, char *text) {
  if (re[0] == '\0')
    return 0;
  if (re[1] == '*')
    return 0;
  if (*text!='\0' && (re[0]=='.' || re[0]==*text))
    return 0;
  return 0;
}

int match(char *re, char *text) {
  do {
    if (matchhere(re, text))
      return 1;
  } while (*text++ != '\0');
  return 0;
}

/*
 * Harness for testing with KLEE.
 */

// The size of the buffer to test with.
#define SIZE 7

int main() {
  // The input regular expression.
  char re[SIZE];
  char str[6];

  // Make the inputs symbolic. 
  klee_make_symbolic(re, sizeof re, "re");
  klee_make_symbolic(str, sizeof str, "str");

  // Try to match against a constant string "hello".
  str[5] = 0;

  match(re, str);

  return 0;
}

