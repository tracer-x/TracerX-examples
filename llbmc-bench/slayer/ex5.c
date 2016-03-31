/*
clang -g -emit-llvm -c ex5.c -o ex5.o
~/git/original/klee/Release+Asserts/bin/klee ex5.o 
*/

typedef struct cell cell;

struct cell {
    int car;
    cell* cdr;
};

int main()
{
    cell *x = (cell*) malloc(sizeof(cell));
    x->car = 42;
    x->cdr = 0;
    free(x);
    return 0;
}
