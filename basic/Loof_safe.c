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
