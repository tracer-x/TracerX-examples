/*
clang -g -emit-llvm -c ex7.c -o ex7.o
~/git/original/klee/Release+Asserts/bin/klee ex7.o 
*/
#include <stdlib.h>
#include <klee/klee.h>

typedef struct _SLL_ENTRY
{
    int Data;
    struct _SLL_ENTRY *Flink;
} SLL_ENTRY, *PSLL_ENTRY;

PSLL_ENTRY SLL_create(int length)
{
    int i;
    PSLL_ENTRY head, tmp;
    head = NULL;
    for(i = 0; i < length; i++) {
        tmp = (PSLL_ENTRY)malloc(sizeof(SLL_ENTRY));
        tmp->Flink = head;
        head = tmp;
    }
    return head;
}

int main(void)
{
    PSLL_ENTRY head;

    int s; 
    klee_make_symbolic(&s, sizeof(s), "s");
    klee_assume(s <= 10);
    head = SLL_create(10);

    return 0;
}
