/*
cd ~/nus/kleetest/llbmc-bench/anonymous
clang -emit-llvm -c intSqRoot_klee.c -o intSqRoot_klee.bc
LD_LIBRARY_PATH=$HOME/z3/z3_install/lib ~/git/tracerx/klee/Release+Asserts/bin/klee intSqRoot_klee.bc   
*/
#include <klee/klee.h>
#include <assert.h>

int main()
{ 
    int N;
    klee_make_symbolic(&N, sizeof(N), "N");
    if(N >= 1 && N <= 200){
	    int r = 1, q = N;
	    while (r + 1 < q) {
		int p = (r + q) / 2;
		if (N < p * p) {
		    q = p;
		} else {
		    r = p;
		}
	    }
	    assert(r * r <= N);
	    assert((r + 1) * (r + 1) > N);
	    return r;
    }
    return 0;
}
