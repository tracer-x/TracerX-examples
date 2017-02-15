/* Basic memory leak example from
 * https://www.owasp.org/index.php/Memory_leak
 *
 * Licensed under creative commons license 3.0, see
 * http://creativecommons.org/licenses/by-sa/3.0/
 */

#include <stdlib.h>
#include <stdio.h>

#define  LOOPS    10
#define  MAXSIZE  256

int main(int argc, char **argv)
{
  int count = 0;
  char *pointer = NULL;

  for(count=0; count<LOOPS; count++) {
    pointer = (char *)malloc(sizeof(char) * MAXSIZE);
  }

  free(pointer);

  return count;
}
