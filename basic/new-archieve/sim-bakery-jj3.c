#include <klee/klee.h>
#define loop for(;;)
#define N 10
#define BOUND 4

#define DEBUG 0
#ifdef DEBUG
#define debug_printf printf
#endif

int pc[N] = {0}, next = 0;
int context, context_switch = 0;
int ticket[N] = {0}; // edit for N

int main() {
    loop {
        int id,c;
        klee_make_symbolic(&c, sizeof(unsigned), "c");
	c = klee_range(0, N, "c");
        for(int i = 0;i<=c;i++){
           id = i;
        }
        if (context != id) context_switch++;
        if (context_switch > BOUND) {    debug_printf("End of path:%d,%d,%d\n",pc[0],pc[1],next);   exit(0);}
        context = id;
        sim(id);
    }
}

int choice(int *i,int z) {
    for(*i = 0;*i<=z;*i++)
      	
    return i;
}

int sim(id) {
    switch (pc[id]) {
        case 0: ticket[id] = next++; pc[id] = 1; debug_printf("case 0, id:%d\n",id); break;
        case 1:if(min(id)){ pc[id] = 2;  debug_printf("case 1, id:%d\n",id);}else exit(0); break; // inline for min()
        case 2: ticket[id] = 0; pc[id] = 0;  debug_printf("case 2, id:%d\n",id);
    }
    klee_assert(alone(id));
}

int min(int id) {
    for (int i = 0; i < N; i++) if (ticket[id] > ticket[i]) return 0;
    return 1;
}

int alone(int id) {
    if (pc[id] != 2) return 1;
    for (int i = 0; i < N; i++) if (i != id && pc[i] == 2) return 0;
}

int debug_printf(const char *format, ...) {}

