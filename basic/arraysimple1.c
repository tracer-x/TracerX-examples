/*
Copyright 2015, 2017 National University of Singapore
cd
cd nus/kleetest
llvm-gcc --emit-llvm -c -g arraysimple2.c
llvm-gcc -S --emit-llvm arraysimple2.c
opt -analyze -dot-cfg arraysimple2.o
klee -write-cvcs -write-pcs -write-paths -write-sym-paths  -write-test-info
-use-query-log=all:pc,all:smt2 -search=dfs arraysimple2.o
ktest-tool --write-ints klee-last/test000001.ktest
ktest-tool --write-ints klee-last/test000002.ktest
ktest-tool --write-ints klee-last/test000003.ktest

*/
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  /*unsigned int a[5];
  a[0] = 0; a[1] = 1; a[2] = 2; 
  unsigned int i;   
  unsigned int j;
  unsigned int idx;
  klee_make_symbolic(&i, sizeof(i), "i");
  klee_make_symbolic(&j, sizeof(j), "j");
  klee_make_symbolic(&idx, sizeof(idx), "idx");
  a[3] = i;
  a[4] = j;
   
  if(idx > 4)
	return 0;

  if(a[idx] != 0)
	a[idx] = 8;

  assert(a[0] == 0);	
  
  return 0;
  */
  unsigned char a[5];
  a[0] = 'a'; a[1] = 'b'; a[2] = 'c'; 
  unsigned char i;   
  unsigned char j;
  unsigned int idx;

#ifdef LLBMC
  i = __llbmc_nondef_unsigned_char();
  j = __llbmc_nondef_unsigned_char();
  idx = __llbmc_nondef_unsigned();
#else
  klee_make_symbolic(&i, sizeof(i), "i");
  klee_make_symbolic(&j, sizeof(j), "j");
  klee_make_symbolic(&idx, sizeof(idx), "idx");
#endif

  a[3] = i;
  a[4] = j;
   
  if(idx > 4)
	return 0;

  if(a[idx] != 'a'){
        a[idx] = 'd';
  }

#ifdef LLBMC
  __llbmc_assert(a[0] == 'a');
#else
  klee_assert(a[0] == 'a');
#endif

  return 0;
} 


