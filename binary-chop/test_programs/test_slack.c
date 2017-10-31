#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int p;
  int a,b;

#ifdef LLBMC
  a = __llbmc_nondef_int();
  b = __llbmc_nondef_int();
#else
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
#endif

  p = 0;

  if (a >= 0){
     p+=10;
  }else{
     p+=20;
  }
  
  if (b >= 0){
     p+=30;
  }else{
     p+=40;
  }
  
  
  klee_assert(p <= 60);
  return 1;

} 
