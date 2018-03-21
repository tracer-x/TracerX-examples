#include <klee/klee.h>

int main() {
  int a[5], b;
  klee_make_symbolic(a, 5 * sizeof(int), "a");
  klee_make_symbolic(&b, sizeof(int), "b");
  a[3] += 5;
  b += 3;
}
