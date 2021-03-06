/*
 * Copyright 2017 National University of Singapore
 *
 * An example for demonstrating subsuming between
 * function invocations in different symbolic execution
 * paths, but the same callsite sequences.
 */

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define LEN 5

void foo3(char *p, char *out) {
  if (*p == 'c')
    *out = 'z';
  else
    *out = *p;

  *(p+1) = *(out+1) = '\0';
}

void foo2(char *p, char *out) {
  if (*p == 'b')
    *out = 'y';
  else
    *out = *p;
  
  if (*p != '\0')
    foo3(p+1, out+1);  
}

void foo1(char *p, char *out) {
  if (*p == 'a')
    *out = 'x';
  else
    *out = *p;
  
  if (*p != '\0')
    foo2(p+1, out+1);  
}


int main(int argc, char **argv) {
  char str[LEN], out[LEN];
  char *p;

#ifdef LLBMC
  for (int i = 0; i < LEN; ++i) {
    str[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(str, LEN, "str");
#endif

  p = str;

  foo1(p, out);

  return 0;
}
