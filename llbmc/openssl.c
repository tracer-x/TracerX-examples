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
    klee_make_symbolic(buf, BUF_SIZE, "buf");

    // Set up string variable 'name' with arbitrary content
    // and length at most MAX_S (including terminator).

    int s = MAX_S;
    char *name = malloc(s);
    name[s-1] = '\0';
    klee_make_symbolic(name, s, "name");


    // Check SSL_get_shared_ciphers for all strings 'name'
    // of size up to MAX_S.

    SSL_get_shared_ciphers(name, buf, BUF_SIZE);

    return 0;
}
