/* 
 * This is an iterative and simplified version of simple regular
 * expression matching. Functionality of matchstar has been removed.
 * In some version of Tracer-X KLEE, this iterative version shows
 * significant space savings in using bounds inequality for memory
 * bounds interpolation, whereas the original version shows almost no
 * difference in space (no. of instructions traversed).
 *
 * This original recursive code with KLEE harness is obtained from the
 * following page of the KLEE tutorial on December 2015:
 * http://klee.github.io/resources/Regexp.c.html
 *
 * From an original in:
 *   The Practice of Programming
 *   Brian W. Kernighan, Rob Pike
 */ 

#include <klee/klee.h>

int match(char *re, char *text) {
  if (re[0] == '^') {
    re++;
    do {
      if (re[0] == '\0')
	return 0;
      if (re[0] == '$' && re[1]=='\0')
	return *text == '\0';
      if (*text!='\0' && (re[0]=='.' || re[0]==*text)) {
	re++; text++;
      } else
	break;
    } while (1);
     
    return 0;
  }
  do {
    char *t = text;
    int status = 0;

    do {
      if (re[0] == '\0')
	break;
      if (re[0] == '$' && re[1]=='\0') {
	status = (*t == '\0');
	break;
      }
      if (*t!='\0' && (re[0]=='.' || re[0]==*t)) {
	re++; t++;
      } else {
	break;
      }
    } while (1);


    if (status)
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
  
  // Make the input symbolic. 
  klee_make_symbolic(re, sizeof re, "re");

  // Try to match against a constant string "hello".
  match(re, "hello");

  return 0;
}

