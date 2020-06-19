#include <klee/klee.h>
int main() 
{ 
  int kappa = 0;
  int ep12, ep32 ,mode1,mode2 ;
  klee_make_symbolic(&ep12, sizeof(int), "ep12");
  klee_make_symbolic(&ep32, sizeof(int), "ep32");
  klee_make_symbolic(&mode1, sizeof(int), "mode1");
  klee_make_symbolic(&mode2, sizeof(int), "mode2");
    
  char r1,nl1  ;
  klee_make_symbolic(&r1, sizeof(char), "r1");
  klee_make_symbolic(&nl1, sizeof(char), "nl1");
  
  if (ep12) ;

  if (ep32>0) ;

  if (mode1) r1++;
  else if (r1) ;
  
  if (mode2) {
    if (ep32>0) ;
    if (ep12)   klee_assert(0);//This lcoation also missed by TX and covered by KLEE
  }

  if (r1) ;
  else if (nl1) ;
}
