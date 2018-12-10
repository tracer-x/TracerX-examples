#include <klee/klee.h>

int main() {
  int wcet;
  int a, b, c;

  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  klee_make_symbolic(&c, sizeof(int), "c");

  wcet = 0;

  if (a <= 0) {
    wcet += 20;
  } else {
    wcet += 10;
  }

  if (a == 1) {
    wcet += 60;
  } else {
    wcet += 50;
  }

  if (b < 0) {
    wcet += 30;
  } else {
    wcet += 40;
  }
  
  if (c < 0) {
    wcet += 70;
  } else {
    wcet += 80;
  }
  
  klee_assert(wcet < 200);
}
