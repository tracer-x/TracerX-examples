/*
 * Copyright 2017 National University of Singapore
 *
 * In some versions of Tracer-X, out-of-bound error at Line 14 gets
 * unreported.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main(int argc, char **argv) {
  char text[3] = "he";
  char *t;
  char data[4];
  char *p;

#ifdef LLBMC
  for (int i = 0; i < 4; ++i) {
    data[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(data, sizeof(data), "data");
#endif

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
