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
 * This program demonstrates the use of tracerx_mark function. It is
 * to be executed with the -output-tree option. Whenever tracerx_mark
 * is visited along the execution, a counter will be incremented, and
 * displayed on the tree in the syntax of "count(s): N (+M)" at each
 * node, where N is the total number of visits of tracerx_mark, and M
 * is the increment for the given node.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

char _bound[6];
char *wcet;

char tracerx_check(char *p) {
  printf("Timing of Path %lu\n", ((uint64_t)p) - ((uint64_t)(&(_bound))));
  return *p;
}

void tracerx_mark(int l) { printf("Line %d visited\n", l); }

static int matchhere(char *, char *);

static int matchstar(int c, char *re, char *text) {
  do {
    if (matchhere(re, text)) {
      wcet++;
      return 1;
    }
  } while (*text != '\0' && (*text++ == c || c == '.'));
  return 0;
}

static int matchhere(char *re, char *text) {
  if (re[0] == '\0') {
    wcet++;
    return 0;
  }
  if (re[1] == '*') {
    return matchstar(re[0], re + 2, text);
  }
  if (re[0] == '$' && re[1] == '\0') {
    wcet++;
    return *text == '\0';
  }
  if (*text != '\0') {
    if (re[0] == '.') {
      tracerx_mark(__LINE__);
    } else if (re[0] == *text) {
    } else {
      goto branch_exit;
    }
    wcet++;
    return matchhere(re + 1, text + 1);
  }
branch_exit:
  return 0;
}

int match(char *re, char *text) {
  if (re[0] == '^') {
    wcet++;
    return matchhere(re + 1, text);
  }
  do {
    if (matchhere(re, text)) {
      wcet++;
      return 1;
    }
  } while (*text++ != '\0');
  return 0;
}

/*
 * Harness for testing with KLEE.
 */

// The size of the buffer to test with.
#define SIZE 4

int main() {
  wcet = _bound;
  // The input regular expression.
  char re[SIZE];

// Make the input symbolic.
#ifdef LLBMC
  for (int i = 0; i < SIZE; ++i) {
    re[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(re, sizeof re, "re");
  klee_assume(re[SIZE - 1] == '\0');
#endif

  // Try to match against a constant string "hello".
  match(re, "hello");
  tracerx_check(wcet);
  return 0;
}
