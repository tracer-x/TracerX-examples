/*
  Copyright 2016 National University of Singapore
 
  For this example we need to ensure that the formula
  constructed for subsumption check is correct. In some
  versions of Tracer-X, the global version of int x
  is considered a composite allocation.

cd
cd nus/kleetest
clang -g -emit-llvm -c argument.c -o argument.bc
 ~/git/tracerx/klee/Release+Asserts/bin/klee -only-output-states-covering-new -search=dfs argument.bc --sym-arg 1 --sym-arg 1 --sym-arg 1 
 */

 #include <stdio.h>

 int main (int argc, char **argv) {
 
   int test = 0;
   for (int i=0; i< argc; i++) {
     printf("argument %d:%s\n", i+1, argv[i]);  
   }
   return 0;
}
