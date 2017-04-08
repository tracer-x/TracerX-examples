/*
 * Test code from simple regular expression matching.
 *
 * A modification of the code with KLEE harness from the
 * following page of the KLEE tutorial:
 *   http://klee.github.io/resources/Regexp.c.html
 *
 * This triggered an assertion failure.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

static int matchhere(char*,char*);

static int matchstar(int c, char *re, char *text) {
  do {
    if (matchhere(re, text))
      return 1;
  } while (*text++ == c);
  return 0;
}

static int matchhere(char *re, char *text) {
  if (re[0] == '\0')
   return 0;
  return matchstar(re[0], re+2, text);
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
#define SIZE 5

int main() {
  // The input regular expression.
  char re[SIZE];

// Make the input symbolic.
#ifdef LLBMC
  for (int i = 0; i < sizeof(re); ++i) {
    re[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(re, sizeof re, "re");
#endif

  // Try to match against a constant string "h".
  match(re, "h");

  return 0;
}

