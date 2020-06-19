#include <klee/klee.h>

int main() {
  int wcet;
  int a, b, c;

  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  klee_make_symbolic(&c, sizeof(int), "c");

  wcet = 0;

  if (a >= 0) {
    wcet += 51;
  } else {
    wcet += 50;
  }

  if (a != 1) {
    wcet += 49;
  } else {
    wcet += 50;
  }

  if (b < 0) {
    wcet += 1;
  } else {
    wcet += 2;
  }

  if (c < 0) {
    wcet += 1;
  } else {
    wcet += 2;
  }

  klee_assert(wcet < 106);
}
