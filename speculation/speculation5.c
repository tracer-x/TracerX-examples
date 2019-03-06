#include <klee/klee.h>

int main() {
  int arg;
  int a;

  klee_make_symbolic(&a, sizeof(int), "a");
  if (a >= 0) arg = 2;
  else arg = 1;


  char b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10;
  int x = 0;

#ifdef LLBMC
  b0 = __llbmc_nondef_char();
  b1 = __llbmc_nondef_char();
  b2 = __llbmc_nondef_char();
  b3 = __llbmc_nondef_char();
  b4 = __llbmc_nondef_char();
  b5 = __llbmc_nondef_char();
  b6 = __llbmc_nondef_char();
  b7 = __llbmc_nondef_char();
  b8 = __llbmc_nondef_char();
  b9 = __llbmc_nondef_char();
#else
  klee_make_symbolic(&b0, sizeof(char), "b0");
  klee_make_symbolic(&b1, sizeof(char), "b1");
  klee_make_symbolic(&b2, sizeof(char), "b2");
  klee_make_symbolic(&b3, sizeof(char), "b3");
  klee_make_symbolic(&b4, sizeof(char), "b4");
  klee_make_symbolic(&b5, sizeof(char), "b5");
  klee_make_symbolic(&b6, sizeof(char), "b6");
  klee_make_symbolic(&b7, sizeof(char), "b7");
  klee_make_symbolic(&b8, sizeof(char), "b8");
  klee_make_symbolic(&b9, sizeof(char), "b9");
#endif

  if (b0 > 0)
    x += 1;
  else
    x += 2;
  if (b1 > 0)
    x += 3;
  else
    x += 4;
  if (b2 > 0)
    x += 5;
  else
    x += 6;
  if (b3 > 0)
    x += 7;
  else
    x += 8;
  if (b4 > 0)
    x += 9;
  else
    x += 10;
  if (b5 > 0)
    x += 11;
  else
    x += 12;
  if (b6 > 0)
    x += 13;
  else
    x += 14;
  if (b3 > 0)
    x += 15;
  else
    x += 16;
  if (b8 > 0)
    x += 17;
  else
    x += 18;
  if (b9 > 0)
    x += 19;
  else
    x += 20;

  klee_assert(x != 99000);

  if (arg == 2)  klee_assert(0);
}
