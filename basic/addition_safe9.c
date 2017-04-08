/*
Copyright 2016, 2017 National University of Singapore

clang -emit-llvm -c -g addition_safe9.c -o addition_safe9.bc
time ~/git/original/klee/Release+Asserts/bin/klee -allow-external-sym-calls
-only-output-states-covering-new -search=dfs addition_safe9.bc 2>log


*/
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#include <assert.h>
#endif

int y;

int add(int p1, int p2, int p3, int x, int y, int z) {
#ifdef LLBMC
  __llbmc_assume(x <= 0);
  __llbmc_assume(y >= 0);
  __llbmc_assume(y <= 35);
  __llbmc_assume(z >= 0);
  __llbmc_assume(z <= 35);
#else
  klee_assume(x <= 0);
  klee_assume(y >= 0);
  klee_assume(y <= 35);
  klee_assume(z >= 0);
  klee_assume(z <= 35);
#endif

  if (p1 > 8) {
    x = x + 1;
    x = x + y;
    x = x + z;
  } else
    x = x + 2;
  if (p2 > 8)
    x = x + 1;
  else {
    x = x + 2;
  }
  if (p3 > 8) {
    x = x + 1;
  } else {
    x = x + y;
    x = x + z;
  }

#ifdef LLBMC
  __llbmc_assert(x <= (2 * y + 6 + 2 * z));
#else
  klee_assert(x <= (2 * y + 6 + 2 * z));
#endif
  return x;
}
int main() {
  int p1, p2, p3, x, z;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  x = __llbmc_nondef_int();
  y = __llbmc_nondef_int();
  z = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");
  klee_make_symbolic(&z, sizeof(z), "z");
#endif

  return add(p1, p2, p3, x, y, z);
}
