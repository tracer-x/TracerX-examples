#include<stdio.h>
#include <stdlib.h>

#define loop for(;;)
#define INF 999999
#define N 2
#define MAXDB 999999
#define LIMIT 3;

int searchspace = 0;

struct systemstate { int next, depth, pc[N], ticket[N], limit[N]; } ss;
int interpolants_ticket[MAXDB][N] = {-1};
int interpolants_pc[MAXDB][N] = {-1};
int interpolants_limit[MAXDB][N] = {-1};
int n_intp = 0;

int init();
int search ();
int alone(int id);
int minticket(int id);
int store_interpolant();
int check_one_interpolant(int a[], int b[]);
int check_one_interpolant_pc(int a[], int b[]);
int check_all_interpolant();
int subsumed();
int print_pc();
int print_tickets();
int print_intp(int i);
int perm_pc(int a[], int b[]);
int perm_ticket(int a[], int b[]);
int symm();


int main() { init(); search(); }

int init() { 
    ss.next = 1; ss.depth = 0; 
    for (int id = 0; id < N; id++) { ss.pc[id] = 0; ss.ticket[id] = INF; ss.limit[id] = LIMIT; }
}

int search () {
    for (int i = 0; i < ss.depth; i++) printf("    ");
    printf("%6d: depth %d next %d ", searchspace, ss.depth, ss.next); print_pc();
    struct systemstate ss0;
    ss.depth++; 

    // if (searchspace > 199) exit(0);

    if (subsumed()) { printf("SUBS\n"); return 1; }
    // if (symm()) { printf("SYMM "); print_pc(); return 1; }
    searchspace++;   
    ss0 = ss;
    
    for (int id = 0; id < N; id++) {

        if (!ss.limit[id]) return 1;  ss.limit[id]--;

        switch (ss.pc[id]) {
            case 0: ss.ticket[id] = ss.next++; ss.pc[id] = 1; search(); break;
            case 1: if (/*ss.ticket[id] = 5 ||*/ minticket(id)) { ss.pc[id] = 2; alone(id); search(); } break;
            case 2: ss.ticket[id] = INF; ss.pc[id] = 0; search();
        }
        NEXT_ID: 
            ss = ss0;
    }
    store_interpolant();
}      

int alone(int id) {
     // printf("ALONE CHECK "); print_pc(); 
      for (int i = 0; i < N; i++) if (i != id && ss.pc[i] == 2) { printf("ERROR!\n"); exit(0); }
     return 1;
}

int minticket(int id) {
    for (int i = 0; i < N; i++) if (ss.ticket[id] > ss.ticket[i]) return 0;
    return 1;
}

int store_interpolant() {
    int i, tmp[N], min, col = 0;

    printf("Storing Intp %d ", n_intp); print_pc();
    print_tickets();
    for (int id = 0; id < N; id++) tmp[id] = ss.ticket[id];
    for (int id = 0; id < N; id++) {
        min = 0;
        for (int j = 0; j < N; j++) if (tmp[j] < tmp[min]) min = j;
        if (tmp[min] == INF) break;
        tmp[min] = INF;
        interpolants_ticket[n_intp][col++] = min;
    }
    interpolants_ticket[n_intp][col] = -1;
    print_intp(n_intp);
    if (!check_all_interpolant()) {
        for (int id = 0; id < N; id++) interpolants_pc[n_intp][id] = ss.pc[id];
        for (int id = 0; id < N; id++) interpolants_limit[n_intp][id] = ss.limit[id];
        n_intp++;
    }

}

int check_one_interpolant_ticket(int a[], int b[]) {
    int i = 0;
    loop { 
        if (a[i] == -1)
            if (b[i] == -1) return 1; else return 0;
        if (a[i] != b[i]) return 0; 
        i++; 
    }
    return 1;
}

int check_one_interpolant_pc(int a[], int b[]) {
    for (int id = 0; id < N; id++) if (a[id] != b[id]) return 0;
    return 1;
}

int check_one_interpolant_limit(int a[], int b[]) {
    for (int id = 0; id < N; id++) if (a[id] != b[id]) return 0;
    return 1;
}

int check_all_interpolant() {
    for (int i = 0; i < n_intp; i++)
        if (check_one_interpolant_ticket(interpolants_ticket[i], interpolants_ticket[n_intp])) 
            if (check_one_interpolant_pc(interpolants_pc[i], interpolants_pc[n_intp])) 
                if (check_one_interpolant_limit(interpolants_limit[i], interpolants_limit[n_intp])) 
                    return 1;
    return 0;
}

int subsumed() {
    int tmp[N], col = 0, min, flag = 0, ticket_count = 0;
    
    for (int i = 0; i < N; i++) { tmp[i] = ss.ticket[i]; if (tmp[i] != INF) ticket_count++; }
    for (int i = 0; i < n_intp; i++) {
        for (int id = 0; id < N; id++) if (interpolants_pc[i][id] != ss.pc[id]) continue;
        for (int id = 0; id < N; id++) if (interpolants_limit[i][id] > ss.limit[id]) continue;
        for (col = 0, flag = 0; interpolants_ticket[i][col] != -1; col++) {
            min = interpolants_ticket[i][col];
            for (int k = 0; k < N; k++) if (tmp[min] > tmp[k]) flag = 1;
            tmp[min] = INF;
        }
        if (col == ticket_count && !flag) {    printf("SUBS:%d ", i); return 1 ;}
    }
    return 0;
}

int print_pc() {
    printf("pc: ");
    for (int id = 0; id < N; id++) printf("%d ", ss.pc[id]);
    printf("\n");
}

int print_tickets() {
    printf("tickets: ");
    for (int id = 0; id < N; id++) printf("%d ", ss.ticket[id]);
    printf("\n");
}

int print_intp(int i) {
    printf("Intp [%d]: ", i);
    for (int col = 0; interpolants_ticket[i][col] != -1; col++) printf("%d ", interpolants_ticket[i][col]);
    printf("\n");
}

// int symm(); // pc1 and pc2 permuted by perm[], ticket order also permuted by perm[]

int perm[N];

int perm_pc(int a[], int b[]) {
    int tmp[N], count = 0;

/*
printf("Perm PC: \n");
for (int i = 0; i < N; i++) printf(" %d ", a[i]); 
printf("\n");
for (int i = 0; i < N; i++) printf(" %d ", b[i]);
printf("\n");
*/

    for (int i = 0; i < N; i++) tmp[i] = b[i];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (a[i] == tmp[j]) { count++; perm[i] = j; tmp[j] = -1; break; }
 
/*
for (int i = 0; i < N; i++) printf(" %d ", perm[i]);
printf("\nCOUNT %d\n", count);
*/
   return (count == N);
}

int perm_ticket(int a[], int b[]) {
    int tmp[N], min;
    for (int i = 0; i < N; i++) tmp[i] = b[i];

    for (int i = 0; a[i] != -1; i++) {
        min = perm[a[i]];
        for (int k = 0; k < N; k++) if (tmp[min] > tmp[k]) return 0;
        tmp[min] = INF;
     }
     for (int i = 0; i < N; i++) if (tmp[i] != INF) return 0;
     return 1;
}

int symm() {
    int tmp[N];
    for (int i = 0; i < N; i++) tmp[i] = ss.pc[i];
    for (int i = 0; i < n_intp; i++) {
        if (!perm_pc(interpolants_pc[i], tmp)) continue;
        if (!perm_ticket(interpolants_ticket[i], ss.ticket)) continue;
        return 1;
    }
    return 0;
}
