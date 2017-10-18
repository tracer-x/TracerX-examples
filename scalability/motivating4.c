/*
 * Copyright 2017 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main(int argc, char **argv)
{
  char a[1 << 20];
  char *p = a;
  char p0;
  char p1;
  char p2;
  char p3;
  char p4;
  char p5;
  char p6;
  char p7;
  char p8;
  char p9;
  char p10;
  char p11;
  char p12;
  char p13;
  char p14;
  char p15;
  char p16;
  char p17;
  char p18;
  char p19;

#ifdef LLBMC
  p0 = __llbmc_nondef_char();
  p1 = __llbmc_nondef_char();
  p2 = __llbmc_nondef_char();
  p3 = __llbmc_nondef_char();
  p4 = __llbmc_nondef_char();
  p5 = __llbmc_nondef_char();
  p6 = __llbmc_nondef_char();
  p7 = __llbmc_nondef_char();
  p8 = __llbmc_nondef_char();
  p9 = __llbmc_nondef_char();
  p10 = __llbmc_nondef_char();
  p11 = __llbmc_nondef_char();
  p12 = __llbmc_nondef_char();
  p13 = __llbmc_nondef_char();
  p14 = __llbmc_nondef_char();
  p15 = __llbmc_nondef_char();
  p16 = __llbmc_nondef_char();
  p17 = __llbmc_nondef_char();
  p18 = __llbmc_nondef_char();
  p19 = __llbmc_nondef_char();
#else
  klee_make_symbolic(&p0, sizeof(p0), "p0");
  klee_make_symbolic(&p1, sizeof(p1), "p1");
  klee_make_symbolic(&p2, sizeof(p2), "p2");
  klee_make_symbolic(&p3, sizeof(p3), "p3");
  klee_make_symbolic(&p4, sizeof(p4), "p4");
  klee_make_symbolic(&p5, sizeof(p5), "p5");
  klee_make_symbolic(&p6, sizeof(p6), "p6");
  klee_make_symbolic(&p7, sizeof(p7), "p7");
  klee_make_symbolic(&p8, sizeof(p8), "p8");
  klee_make_symbolic(&p9, sizeof(p9), "p9");
  klee_make_symbolic(&p10, sizeof(p10), "p10");
  klee_make_symbolic(&p11, sizeof(p11), "p11");
  klee_make_symbolic(&p12, sizeof(p12), "p12");
  klee_make_symbolic(&p13, sizeof(p13), "p13");
  klee_make_symbolic(&p14, sizeof(p14), "p14");
  klee_make_symbolic(&p15, sizeof(p15), "p15");
  klee_make_symbolic(&p16, sizeof(p16), "p16");
  klee_make_symbolic(&p17, sizeof(p17), "p17");
  klee_make_symbolic(&p18, sizeof(p18), "p18");
  klee_make_symbolic(&p19, sizeof(p19), "p19");
#endif

  if (p0) p += 3; else p += 1 << 0;
  if (p1) p += 3; else p += 1 << 1;
  if (p2) p += 3; else p += 1 << 2;
  if (p3) p += 3; else p += 1 << 3;
  if (p4) p += 3; else p += 1 << 4;
  if (p5) p += 3; else p += 1 << 5;
  if (p6) p += 3; else p += 1 << 6;
  if (p7) p += 3; else p += 1 << 7;
  if (p8) p += 3; else p += 1 << 8;
  if (p9) p += 3; else p += 1 << 9;
  if (p10) p += 3; else p += 1 << 10;
  if (p11) p += 3; else p += 1 << 11;
  if (p12) p += 3; else p += 1 << 12;
  if (p13) p += 3; else p += 1 << 13;
  if (p14) p += 3; else p += 1 << 14;
  if (p15) p += 3; else p += 1 << 15;
  if (p16) p += 3; else p += 1 << 16;
  if (p17) p += 3; else p += 1 << 17;
  if (p18) p += 3; else p += 1 << 18;
  if (p19) p += 3; else p += 1 << 19;

  return *p;
}

