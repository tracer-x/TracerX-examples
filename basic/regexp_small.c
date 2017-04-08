/*
 * Simple regular expression matching.
 *
 * From:
 *   The Practice of Programming
 *   Brian W. Kernighan, Rob Pike
 *
 * This code with KLEE harness is obtained from the following
 * page of the KLEE tutorial on December 2015:
 *   http://klee.github.io/resources/Regexp.c.html
 *
 * This is a "small" version where both the inputs are smaller
 * in size and parts of the code have been commented out.
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
  } while (*text != '\0' && (*text++ == c || c== '.'));
  return 0;
}

static int matchhere(char *re, char *text) {
  if (re[0] == '\0')
    return 0;
  if (re[1] == '*')
    return matchstar(re[0], re+2, text);
  // if (re[0] == '$' && re[1]=='\0')
  //  return *text == '\0';
  if (*text!='\0' && (
		      // re[0]=='.' ||
		      re[0]==*text
		      )
      )
    return matchhere(re+1, text+1);
  return 0;
}

int match(char *re, char *text) {
  // if (re[0] == '^')
  // return matchhere(re+1, text);
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

