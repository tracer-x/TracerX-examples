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
  char a[112];
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

  if (p0) {} else p += 1;
  if (p1) {} else p += 1;
  if (p2) {} else p += 1;
  if (p3) {} else p += 1;
  if (p4) {} else p += 1;
  if (p5) {} else p += 1;
  if (p6) {} else p += 1;
  if (p7) {} else p += 1;
  if (p8) {} else p += 1;
  if (p9) {} else p += 1;
  if (p10) {} else p += 1;
  if (p11) {} else p += 1;
  if (p12) {} else p += 1;
  if (p13) {} else p += 1;
  if (p14) {} else p += 1;
  if (p15) {} else p += 1;
  if (p16) {} else p += 1;
  if (p17) {} else p += 1;
  if (p18) {} else p += 1;
  if (p19) {} else p += 1;
  if (p20) {} else p += 1;
  if (p21) {} else p += 1;
  if (p22) {} else p += 1;
  if (p23) {} else p += 1;
  if (p24) {} else p += 1;
  if (p25) {} else p += 1;
  if (p26) {} else p += 1;
  if (p27) {} else p += 1;
  if (p28) {} else p += 1;
  if (p29) {} else p += 1;

  return *p;
}

