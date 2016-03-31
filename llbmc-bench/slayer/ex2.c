/*
clang -g -emit-llvm -c ex2.c -o ex2.o
~/git/original/klee/Release+Asserts/bin/klee ex2.o 
*/

int main()
{
    int x;
    int *y = 0;
    x = *y;
    return 0;
}
