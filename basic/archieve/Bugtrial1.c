#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include<assert.h>
int main()
{
int a[3]={0};
int i,j;
klee_make_symbolic(&i, sizeof(int), "i");
klee_make_symbolic(&j, sizeof(int), "j");
klee_assume(0<=i);
klee_assume(i<=1);
klee_assume(1<=j);
klee_assume(j<=2);
a[i]=55;
a[j]=66;
a[0]=5;
//klee_assert(a[i]==55);
}

