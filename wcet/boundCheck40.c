/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation: it
 * should have interpolations not just at/near the end of the traces.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

void tracerx_check(void *p) { *p; } 

int main(int argc, char **argv)
{
  char s[1621];
  int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20;
  int p21, p22, p23, p24, p25,p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40;
  char *p;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  p4 = __llbmc_nondef_int();
  p5 = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(int), "p1");
  klee_make_symbolic(&p2, sizeof(int), "p2");
  klee_make_symbolic(&p3, sizeof(int), "p3");
  klee_make_symbolic(&p4, sizeof(int), "p4");
  klee_make_symbolic(&p5, sizeof(int), "p5");
#endif

  p = s;

  if (p1) {
    p += 1;
  } else {
    p += 2;
  }
  if (p2) {
    p += 3;
  } else {
    p += 4;
  }
  if (p3) {
    p += 5;
  } else {
    p += 6;
  }
  if (p4) {
    p += 7;
  } else {
    p += 8;
  }
  if (p5) {
    p += 9;
  } else {
    p += 10;
  }
  if (p6) {
    p += 11;
  } else {
    p += 12;
  }
  if (p7) {
    p += 13;
  } else {
    p += 14;
  }
  if (p8) {
    p += 15;
  } else {
    p += 16;
  }
  if (p9) {
    p += 17;
  } else {
    p += 18;
  }
  if (p10) {
    p += 19;
  } else {
    p += 20;
  }
  if (p11) {
    p += 21;
  } else {
    p += 22;
  }
  if (p12) {
    p += 23;
  } else {
    p += 24;
  }
  if (p13) {
    p += 25;
  } else {
    p += 26;
  }
  if (p14) {
    p += 27;
  } else {
    p += 28;
  }
  if (p15) {
    p += 29;
  } else {
    p += 30;
  }
  if (p16) {
    p += 31;
  } else {
    p += 32;
  }
  if (p17) {
    p += 33;
  } else {
    p += 34;
  }
  if (p18) {
    p += 35;
  } else {
    p += 36;
  }
  if (p19) {
    p += 37;
  } else {
    p += 38;
  }
  if (p20) {
    p += 39;
  } else {
    p += 40;
  }
  if (p21) {
    p += 41;
  } else {
    p += 42;
  }
  if (p22) {
    p += 43;
  } else {
    p += 44;
  }
  if (p23) {
    p += 45;
  } else {
    p += 46;
  }
  if (p24) {
    p += 47;
  } else {
    p += 48;
  }
  if (p25) {
    p += 49;
  } else {
    p += 50;
  }
  if (p26) {
    p +=51;
  } else {
    p += 52;
  }
  if (p27) {
    p += 53;
  } else {
    p += 54;
  }
  if (p28) {
    p += 55;
  } else {
    p += 56;
  }
  if (p29) {
    p += 57;
  } else {
    p += 58;
  }
  if (p30) {
    p += 59;
  } else {
    p += 60;
  }
  if (p31) {
    p += 61;
  } else {
    p += 62;
  }
  if (p32) {
    p += 63;
  } else {
    p += 64;
  }
  if (p33) {
    p += 65;
  } else {
    p += 66;
  }
  if (p34) {
    p += 67;
  } else {
    p += 68;
  }
  if (p35) {
    p += 69;
  } else {
    p += 70;
  }
  if (p36) {
    p += 71;
  } else {
    p += 72;
  }
  if (p37) {
    p += 73;
  } else {
    p += 74;
  }
  if (p38) {
    p += 75;
  } else {
    p += 76;
  }
  if (p39) {
    p += 77;
  } else {
    p += 78;
  }
  if (p40) {
    p += 79;
  } else {
    p += 80;
  }

  // p should be in s
#ifdef LLBMC
    __llbmc_assert(p < s+1621);
#else
  tracerx_check(*p);
#endif


}

