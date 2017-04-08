/* Use-after-free example
 *
 * Copyright 2017 National University of Singapore
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char *p = (char *) malloc(10);
  
  strcpy(p, "hello");
  
  free(p);

  return p[2];
}
