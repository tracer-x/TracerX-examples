/*
clang -emit-llvm -g -c fib_eq.c
time /home/felicia/git/original/klee/Release+Asserts/bin/klee -max-time=10 -search=dfs -output-dir=fib_eq.stpklee fib_eq.bc

*/

#include <klee/klee.h>
#include <assert.h>

unsigned fib_opt(unsigned n) {
  int f1=0,f2=1,f;
  do{
  	f=f1+f2;
  	f1=f2;
  	f2=f;
  	n--;
  }while(n>1);
  return f;
}
unsigned fib(unsigned n) {
   if ( n == 0 )
      return 0;
   else if ( n == 1 )
      return 1;
   else
      return ( fib(n-1) + fib(n-2) );
}

int main() {
 unsigned n;
 klee_make_symbolic(&n, sizeof(n), "n");
 klee_assume(n <= 3);
 assert(fib(n) == fib_opt(n));
 return 0;
}
