#include <klee/klee.h>

int main() {
  int a[10][10], c;
  klee_make_symbolic(&a, 100 * sizeof(int), "a");
  klee_make_symbolic(&c, sizeof(int), "c");
  a[5][3] = c;
}
