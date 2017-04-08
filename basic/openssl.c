/* KLEE adaptation of openssl.c in LLBMC 2013.1
 * Portions Copyright 2016, 2017 National University of Singapore
 *
 * See also LLBMC copyright and license in license/LLBMC_LICENSE.
 */

#include <stdlib.h>

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

char *SSL_get_shared_ciphers(const char *cp, char *buf, int len)
{
    char *p = buf;

    for (; *cp; )
    {
        if (len-- == 0)
        {
            *p='\0';
            return(buf);
        }
        else
            *(p++)= *(cp++);
    }
    *(p++)=':';

    p[-1]='\0';
    return(buf);
}

/* test function */

#define BUF_SIZE 5
#define MAX_S 10

int main()
{
    char *buf = malloc(BUF_SIZE);

#ifdef LLBMC
  for (int i = 0; i < BUF_SIZE; ++i) {
    buf[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(buf, BUF_SIZE, "buf");
#endif

    // Set up string variable 'name' with arbitrary content
    // and length at most MAX_S (including terminator).

    int s = MAX_S;
    char *name = malloc(s);
    name[s-1] = '\0';

#ifdef LLBMC
  for (int i = 0; i < MAX_S; ++i) {
    name[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(name, s, "name");
#endif

    // Check SSL_get_shared_ciphers for all strings 'name'
    // of size up to MAX_S.

    SSL_get_shared_ciphers(name, buf, BUF_SIZE);

    return 0;
}
