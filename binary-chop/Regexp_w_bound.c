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
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

void tracerx_check(void *p) { *p; } 

char s[1000000];
char *p=s;

static int matchhere(char*,char*);

static int matchstar(int c, char *re, char *text) {
  do {
    if (matchhere(re, text)){
      p++;	
      return 1;
    }
  } while (*text != '\0' && (*text++ == c || c== '.'));
  return 0;
}

static int matchhere(char *re, char *text) {
  if (re[0] == '\0'){
     p++;
     return 0;
  }
  if (re[1] == '*'){
    return matchstar(re[0], re+2, text);
    p++;
  }
  if (re[0] == '$' && re[1]=='\0'){
    p++;
    return *text == '\0';
  }
  if (*text!='\0' && (re[0]=='.' || re[0]==*text)){
    p++;
    return matchhere(re+1, text+1);
  }
  return 0;
}

int match(char *re, char *text) {
  if (re[0] == '^'){
    p++;
    return matchhere(re+1, text);
  }
  do {
    if (matchhere(re, text)){
      p++;
      return 1;
    }
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
  p++;

// Make the input symbolic.
#ifdef LLBMC
  for (int i = 0; i < SIZE; ++i) {
    re[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(re, sizeof re, "re");
  klee_assume(re[SIZE-1] == '\0');
#endif

  // Try to match against a constant string "hello".
  match(re, "hello");
  tracerx_check(p);
  return 0;
}

