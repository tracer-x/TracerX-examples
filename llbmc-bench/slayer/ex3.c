/*
clang -g -emit-llvm -c ex3.c -o ex3.o
~/git/original/klee/Release+Asserts/bin/klee ex3.o 
*/


int main()
{
    int *x = (int*)malloc(sizeof(int));
    free(x);
    free(x);
    x = (int*)malloc(sizeof(int));
    return 0;
}
