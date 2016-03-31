/*
clang -emit-llvm -c -g simpleWhile_klee.c -o simpleWhile_klee.bc
time ~/git/original/klee/Release+Asserts/bin/klee -allow-external-sym-calls -only-output-states-covering-new -search=dfs simpleWhile_klee.bc

clang -emit-llvm -c -g simpleWhile_klee.c -o simpleWhile_klee.bc
time ~/git/tracerx/klee/Release+Asserts/bin/klee -allow-external-sym-calls -only-output-states-covering-new -search=dfs simpleWhile_klee.bc 2>log

home/felicia/nus/kleetest/llbmc-bench/anonymous/simpleWhile_klee.bc
*/
#include <klee/klee.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    int N;    
    klee_make_symbolic(&N, sizeof(N), "N");
    klee_assume(0 <= N);
    klee_assume(N <= 4);

    int x = 0, i = 0;
    while (i < N) {
	if (i % 2 == 0) {
	    x += 2;
	}
	i++;
    }
    assert(x == N || x == N + 1); // x == N if N is even, otherwise N is odd
    
    return 0;
}
