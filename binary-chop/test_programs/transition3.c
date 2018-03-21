#include <klee/klee.h>

int main() {
  long int a[5], b;
  klee_make_symbolic(a, 5 * sizeof(long int), "a");
  klee_make_symbolic(&b, sizeof(long int), "b");
  a[3] += 5;
  b += 3;
}
