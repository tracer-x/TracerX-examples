#include <klee/klee.h>
#define loop for(;;)
#define INF 99999
#define N 6
#define BOUND 12

int main() {
int pc[N] = {0}, next = 0;
int context, context_switch = 0;
// int ticket[N] = {0}; // edit for N
int t0 = INF, t1 = INF, t2 = INF, t3 = INF, t4 = INF, t5 = INF;

    loop {
        int id, x;
        klee_make_symbolic(&id, sizeof(unsigned), "id");
        if (id != 0) {
            if (id != 1) {
                if (id != 2) {
                    if (id != 3) {
                        if (id != 4) x = 5; else x = 4;
                    } else x = 3;
                } else x = 2;
            } else x = 1;
        } else x = 0;

        if (context != x) context_switch++;
        if (context_switch > BOUND) { printf("End of path:%d,%d,%d\n",pc[0],pc[1],next);   exit(0);}
        context = x;
	id = x;
	int tt;
	    switch (pc[id]) {
		case 0: 
		    switch (id) {
		        case 0: t0 = ++next; break;
		        case 1: t1 = ++next; break;
		        case 2: t2 = ++next; break;
		        case 3: t3 = ++next; break;
		        case 4: t4 = ++next; break;
		        case 5: t5 = ++next; 
		    }
		    pc[id] = 1;
		    break;
		case 1:           
		    switch (id) {
		        case 0: tt = t0; break;
		        case 1: tt = t1; break;
		        case 2: tt = t2; break;
		        case 3: tt = t3; break;
		        case 4: tt = t4; break;
		        case 5: tt = t5; 
		     }
		     if (tt<=t0 && tt<=t1 && tt<=t2 && tt<=t3 && tt<=t4 && tt<=t5) 
		             { pc[id] = 2; 
		              int a = 1; 
		              for (int i = 0; i < N; i++) if (i != id && pc[i] == 2) a = 0;
		              klee_assert(a); 
		              break; }
		     exit(0);
		case 2: 
		    switch (id) {
		        case 0: t0 = INF; break;
		        case 1: t1 = INF; break;
		        case 2: t2 = INF; break;
		        case 3: t3 = INF; break;
		        case 4: t4 = INF; break;
		        case 5: t5 = INF;
		    }
		    pc[id] = 0; exit(0);
	    }

    }
}

