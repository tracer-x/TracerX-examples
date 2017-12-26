#include <klee/klee.h>

int main() {
  int a, b;
  klee_make_symbolic(&a, sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  a += 5;
  b += 3;
}
