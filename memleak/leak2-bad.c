/* Basic memory leak example from
 * https://www.owasp.org/index.php/Memory_leak
 * with modifications.
 *
 * Portions copyright 2017 National University of Singapore
 *
 * Licensed under creative commons license 3.0, see
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#include <stdlib.h>
#include <unistd.h>

#define BLOCK_SIZE  256

/* According to https://www.owasp.org/index.php/Memory_leak, this C
 * function leaks a block of allocated memory if the call to read()
 * fails to return the expected number of bytes.
 */
char* getBlock(int fd) {
  char* buf = (char*) malloc(BLOCK_SIZE);
  if (!buf) {
    return NULL;
  }
  if (read(fd, buf, BLOCK_SIZE) != BLOCK_SIZE) {
    return NULL;
  }
  return buf;
}

int main(int argc, char **argv)
{
  char *pointer = getBlock(100);

  if (pointer != NULL)
    free(pointer);

  return 0;
}
