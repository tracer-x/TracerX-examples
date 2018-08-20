// KLEE: done: total instructions = 141619
// KLEE: done: completed paths = 9902, among which
// KLEE: done:     early-terminating paths (instruction time limit, solver
// timeout, max-depth reached) = 0
// KLEE: done:     average branching depth of completed paths = 100
// KLEE: done:     average branching depth of subsumed paths = 67.6667
// KLEE: done:     average instructions of completed paths = 1369
// KLEE: done:     average instructions of subsumed paths = 918.5
// KLEE: done:     subsumed paths = 9702
// KLEE: done:     error paths = 1
// KLEE: done:     program exit paths = 199
// KLEE: done: generated tests = 4, among which
// KLEE: done:     early-terminating tests (instruction time limit, solver
// timeout, max-depth reached) = 0
// KLEE: done:     error tests = 1
// KLEE: done:     program exit tests = 3 

#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int main() {
  int y,j=0;


  klee_make_symbolic(&y, sizeof(y), "y");

  int i=0;
  for (;i<100;i++){
    int x;
    klee_make_symbolic(&x, sizeof(x), "x");
    if(x > 0)
       j++;
  }
  printf("%d\n",j);
  klee_assert (j<100) ;
    
  return 0;
} 

