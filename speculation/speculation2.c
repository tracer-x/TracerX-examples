#include <klee/klee.h>

int main() {
  int wcet;
  int a, b, c;

  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  klee_make_symbolic(&c, sizeof(int), "c");

  wcet = 0;

  // klee_assume(a < b);
  // a = 5;

  if (a >= 0) {
    wcet += 51;
  } else {
    wcet += 50;
  }
}
