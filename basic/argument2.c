/*
  Copyright 2016 National University of Singapore
cd
cd git/klee-examples/basic
clang -g -emit-llvm -c argument2.c -o argument2.bc
 ~/git/tracerx/klee/Release+Asserts/bin/klee -only-output-states-covering-new -search=dfs argument2.bc --sym-arg 1 --sym-arg 1 --sym-arg 1 
 */

 #include <stdio.h>

 int main (int argc, char **argv) {
 
   int test = 0;
   int i = 1;
   if (argc > 1) {
     if(argv[i][0])
     	printf("argument2 test"); 
   }

   register unsigned char *ptr;
   for(ptr = (unsigned char *) &argv[i][1]; *ptr; ptr++) {  
     printf("success: load from pointer\n");
   }

   return 0;
}
