/*
clang -emit-llvm -c -g selectSort_klee.c -o selectSort_klee.o
time ~/git/original/klee/Release+Asserts/bin/klee -only-output-states-covering-new selectSort_klee.o 
*/
#include <klee/klee.h>
#include <stdlib.h>
#include <assert.h>

void selectSort(int *a, int N)
{
    int j, i;
    for (j = 0; j < N - 1; j++) {
        int min = j;
        for (i = j + 1; i < N; i++) {
            if (a[min] > a[i]) {
                min = i;
            }
        }
        int t = a[j];
        a[j] = a[min];
        a[min] = t;
    }
    for (j = 0; j < N - 1; j++) {
        assert(a[j] <= a[j + 1]);
    }
}

int main()
{	
    int N = 7;
    int i;
    int *a = malloc(N * sizeof(int));
    for (i = 0; i < N; i++) {
        int s;
        klee_make_symbolic(&s, sizeof(s), "s");
        a[i] = s;
    }
    //int a[] = {0, 0, 0};
    selectSort(a, N);
    free(a);
    return 0;
}
