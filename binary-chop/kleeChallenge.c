
#include <klee/klee.h>


int kappa = 0;
int main() {

  int q;
  int a, b, c;
  wcet = 0;
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  klee_make_symbolic(&c, sizeof(int), "c");

  q = 5;

  for (int i = 0 ; i<500;i++){
    if (a >= 0) {
      q += 3;
    } else {
      q += 4;
    }
    if (i == 491) {
      if ((a >0 &&  b > 0) || c > 0 )
	q+=7;       
    } else {
      q += 6;
    }
  }
}
