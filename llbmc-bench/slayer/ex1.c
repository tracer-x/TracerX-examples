/*
clang -g -emit-llvm -c ex1.c -o ex1.o
~/git/original/klee/Release+Asserts/bin/klee ex1.o 
*/

int main()
{
    int x;
    free(&x);
    return 0;
}
