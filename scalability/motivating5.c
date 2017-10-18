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
  char a[1 << 30];
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
  char p20;
  char p21;
  char p22;
  char p23;
  char p24;
  char p25;
  char p26;
  char p27;
  char p28;
  char p29;

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
  p20 = __llbmc_nondef_char();
  p21 = __llbmc_nondef_char();
  p22 = __llbmc_nondef_char();
  p23 = __llbmc_nondef_char();
  p24 = __llbmc_nondef_char();
  p25 = __llbmc_nondef_char();
  p26 = __llbmc_nondef_char();
  p27 = __llbmc_nondef_char();
  p28 = __llbmc_nondef_char();
  p29 = __llbmc_nondef_char();
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
  klee_make_symbolic(&p20, sizeof(p20), "p20");
  klee_make_symbolic(&p21, sizeof(p21), "p21");
  klee_make_symbolic(&p22, sizeof(p22), "p22");
  klee_make_symbolic(&p23, sizeof(p23), "p23");
  klee_make_symbolic(&p24, sizeof(p24), "p24");
  klee_make_symbolic(&p25, sizeof(p25), "p25");
  klee_make_symbolic(&p26, sizeof(p26), "p26");
  klee_make_symbolic(&p27, sizeof(p27), "p27");
  klee_make_symbolic(&p28, sizeof(p28), "p28");
  klee_make_symbolic(&p29, sizeof(p29), "p29");
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
  if (p20) p += 3; else p += 1 << 20;
  if (p21) p += 3; else p += 1 << 21;
  if (p22) p += 3; else p += 1 << 22;
  if (p23) p += 3; else p += 1 << 23;
  if (p24) p += 3; else p += 1 << 24;
  if (p25) p += 3; else p += 1 << 25;
  if (p26) p += 3; else p += 1 << 26;
  if (p27) p += 3; else p += 1 << 27;
  if (p28) p += 3; else p += 1 << 28;
  if (p29) p += 3; else p += 1 << 29;

  return *p;
}

