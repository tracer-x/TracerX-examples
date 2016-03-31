/* MDH WCET BENCHMARK SUITE. File version $Id: fac.c,v 1.1 2005/11/11 10:14:54 ael01 Exp $ */
/*
clang -g -emit-llvm -c fac.c -o fac.o
~/git/original/klee/Release+Asserts/bin/klee fac.o 
*/
/*
clang -g -emit-llvm -c fac.c -o fac.o
~/git/original/klee/Release+Asserts/bin/klee fac.o 
*/

 /*
  * Changes: JG 2005/12/23: Inserted prototype.
  *                         Indented program.
  */
int             fac(int n);

int
fac(int n)
{
    if (n == 0)
        return 1;
    else
        return (n * fac(n - 1));
}

int
main()
{
    int             i;
    int             s = 0;

    for (i = 0; i <= 5; i++)
        s += fac(i);

    return s;
}
