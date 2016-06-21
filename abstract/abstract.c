/*
Copyright 2016 National University of Singapore
*/
#include <klee/klee.h>
#include <assert.h>

int main() {
	int count;
	int i;
	klee_make_symbolic(&count, sizeof(count), "count");	
	klee_make_symbolic(&i, sizeof(i), "i");	
	klee_assume(count == 0);
	klee_assume(i == 0);
	klee_abstract(i == 0); 
	klee_abstract(count == 0);
	while(i < 3){
		count++;
		i++;
	}
	klee_assert(count == 3);
}
