/*
clang -g -emit-llvm -c ex6.c -o ex6.o
~/git/original/klee/Release+Asserts/bin/klee ex6.o 
*/
typedef struct cell cell;

struct cell {
    int car;
    cell* cdr;
};

int main() {
    cell *x ;

    if (x) {
        x->car = x->car * 2 ;
        x->cdr = 0;
    } else {
        x = (cell*) malloc(sizeof(cell));
        x->car = 0;
    }

    return 0;
}
