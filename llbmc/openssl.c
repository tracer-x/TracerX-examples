#include <stdlib.h>
#include <klee/klee.h>

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

    // Set up string variable 'name' with arbitrary content
    // and length at most MAX_S (including terminator).

    size_t s;
    klee_make_symbolic(&s, sizeof(s), "s");

    klee_assume(0 < s && s < MAX_S);
    char *name = malloc(s);

    klee_make_symbolic(&name, sizeof(name), "name");

    klee_assume(name[s-1] == '\0');

    // Check SSL_get_shared_ciphers for all strings 'name'
    // of size up to MAX_S.

    SSL_get_shared_ciphers(name, buf, BUF_SIZE);

    return 0;
}
