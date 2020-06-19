#include <klee/klee.h>
#define loop for(;;)
#define N 2
#define BOUND 4

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
        if (context_switch > BOUND) {    printf("End of path:%d,%d,%d\n",pc[0],pc[1],next);   exit(0);}
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
        case 0: printf("case 0, pc0:%d,pc1:%d\n",pc[0],pc[1]); ticket[id] = next++; pc[id] = 1; break;
        case 1:if(min(id)){ printf("case 1, pc0:%d,pc1:%d\n",pc[0],pc[1]); pc[id] = 2; }else exit(0); break; // inline for min()
        case 2: printf("case 2, , pc0:%d,pc1:%d\n\n\n",pc[0],pc[1]); ticket[id] = 0; pc[id] = 0; exit(0); 
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


/*



int sim(int id) {
    int flag;
    switch (pc[id]) {
        case 0: ticket[id] = ++next; pc[id] = 1; break;
        case 1: flag = (
                    ticket[id] <= ticket[0] &&
                    ticket[id] <= ticket[1] &&
                    ticket[id] <= ticket[2] &&
                    ticket[id] <= ticket[3] &&
                    ticket[id] <= ticket[4] &&
                    ticket[id] <= ticket[5] &&
                    ticket[id] <= ticket[6] &&
                    ticket[id] <= ticket[7]);
              klee_assume(flag);
              pc[id] = 2; int a = alone(id); klee_assert(a); break;
        case 2: ticket[id] = 0; pc[id] = 0;
    }
}

int alone(int id) {
    for (int i = 0; i < N; i++) if (i != id && pc[i] == 2) return 0;
    return 1;
}*/
