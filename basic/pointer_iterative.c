/* 
 * Copyright 2017 National University of Singapore
 *
 * In some versions of Tracer-X, out-of-bound error at Line 14 gets
 * unreported.
 */ 

#include <klee/klee.h>

int main(int argc, char **argv) {
  char text[3] = "he";
  char *t;
  char data[4];
  char *p;

  klee_make_symbolic(data, sizeof(data), "data");

  p = data;
  t = text;
  
  while (*t++) {
    if (*p) {
      p+=2;
    } else {
      p++;
    }
  }

  return *p;
}
