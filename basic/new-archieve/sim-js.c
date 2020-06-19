#include <klee/klee.h>

#define loop for(;;)
#define MAXJOB 10
#define MAXTASKPERJOB 6
#define MAXMACHINE 10
#define BOUND 100

#define taskid(j, t)  1000*j + t; 
#define jobsof(tid)  tid / 1000; 
#define taskof(tid)  tid % 1000; 

int jobs[MAXJOB][MAXTASKPERJOB]; // contains machine id, -1 sentinel
int NJOBS;
int NTASKS[MAXJOB];

int nexttask[MAXJOB] = {0};
int duration[MAXJOB][MAXTASKPERJOB];
int frontier [MAXMACHINE]; // machine schedule

int start[MAXJOB][MAXTASKPERJOB];

int main() {
    int choice_vector[MAXTASKPERJOB], nchoices = 0, n;

    init();
    loop {
        for (int j = 0; j < NJOBS; j++) { 
            int t = nexttask[j];
            nchoices = 0;
            if (t != -1) { 
                choice_vector[nchoices++] = taskid(j, t); 
                nexttask[j] = t++; } // Is t correct? 
        }
        choice_vector[nchoices] = -1;
        int tid;
        klee_make_symbolic(&tid, sizeof(unsigned), "tid");
        choice(tid, choice_vector); 
        int j = jobof(tid); int t = taskof(tid);
        int m = jobs[j][t];
        if (t == 0) frontier[m] += duration[j][t];
        else frontier[m] = max(frontier[m], frontier[jobs[j][t-1]]) + duration[j][t];
        if (frontier[m] > BOUND) assert(0);
    }
}

init() { 
    // populate jobs[][]
    // initialize NJOBS and NTASKS[NJOBS]
    // initialize nexttask[0 .. NJOBS-1] to 0;
}

int choice(int z, int *ch) {
    if (*ch == -1) exit(0);
    if (z != *ch) choice(z, ch + 1);
    return z;
}

//    if (z != 0) z=1; 
//    else z = 0;                                                                       

/*int sim(int x, int v) {
   sum += v * weight[x];
   check_infeasible();
   check_goal(x);
}*/
    

