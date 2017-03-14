/* Use-after-free example
 *
 * Copyright 2017 National University of Singapore
 */
#include <klee/klee.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char *p = (char *) malloc(10);
  
  strcpy(p, "hello");
  
  free(p);

  return p[2];
}
