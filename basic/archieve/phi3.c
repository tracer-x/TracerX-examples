#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <klee/klee.h>


int f(int a)
{
	int b = a;
	b = b - 5;
	if (b>10)
		a = 1;
	else
		a = 0;
	return a;
}


int main()
{
        int a;
        klee_make_symbolic(&a,sizeof(int),"a");
	return f(a);
}
