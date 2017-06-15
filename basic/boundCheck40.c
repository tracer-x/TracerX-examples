/*
 * Copyright 2016, 2017 National University of Singapore
 *
 * This program is for testing memory bounds check interpolation: it
 * should have subsumptions not just at/near the end of the traces.
 * TRACER-X can analyze but LLBMC and KLEE can't analyze this program.
 * This program was prepared to test that LLBMC doesn't have bound
 * propagation.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

void tracerx_check(char *p) { *p; } 

char _bound[1651];
char *wcet;

int main(int argc, char **argv)
{
  wcet = _bound;

  int p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20;
  int p21, p22, p23, p24, p25,p26, p27, p28, p29, p30, p31, p32, p33, p34, p35, p36, p37, p38, p39, p40;
  char *p;

#ifdef LLBMC
  p1 = __llbmc_nondef_int();
  p2 = __llbmc_nondef_int();
  p3 = __llbmc_nondef_int();
  p4 = __llbmc_nondef_int();
  p5 = __llbmc_nondef_int();
  p6 = __llbmc_nondef_int();
  p7 = __llbmc_nondef_int();
  p8 = __llbmc_nondef_int();
  p9 = __llbmc_nondef_int();
  p10 = __llbmc_nondef_int();
  p11 = __llbmc_nondef_int();
  p12 = __llbmc_nondef_int();
  p13 = __llbmc_nondef_int();
  p14 = __llbmc_nondef_int();
  p15 = __llbmc_nondef_int();
  p16 = __llbmc_nondef_int();
  p17 = __llbmc_nondef_int();
  p18 = __llbmc_nondef_int();
  p19 = __llbmc_nondef_int();
  p20 = __llbmc_nondef_int();
  p21 = __llbmc_nondef_int();
  p22 = __llbmc_nondef_int();
  p23 = __llbmc_nondef_int();
  p24 = __llbmc_nondef_int();
  p25 = __llbmc_nondef_int();
  p26 = __llbmc_nondef_int();
  p27 = __llbmc_nondef_int();
  p28 = __llbmc_nondef_int();
  p29 = __llbmc_nondef_int();
  p30 = __llbmc_nondef_int();
  p31 = __llbmc_nondef_int();
  p32 = __llbmc_nondef_int();
  p33 = __llbmc_nondef_int();
  p34 = __llbmc_nondef_int();
  p35 = __llbmc_nondef_int();
  p36 = __llbmc_nondef_int();
  p37 = __llbmc_nondef_int();
  p38 = __llbmc_nondef_int();
  p39 = __llbmc_nondef_int();
  p40 = __llbmc_nondef_int();
#else
  klee_make_symbolic(&p1, sizeof(int), "p1");
  klee_make_symbolic(&p2, sizeof(int), "p2");
  klee_make_symbolic(&p3, sizeof(int), "p3");
  klee_make_symbolic(&p4, sizeof(int), "p4");
  klee_make_symbolic(&p5, sizeof(int), "p5");
  klee_make_symbolic(&p6, sizeof(int), "p6");
  klee_make_symbolic(&p7, sizeof(int), "p7");
  klee_make_symbolic(&p8, sizeof(int), "p8");
  klee_make_symbolic(&p9, sizeof(int), "p9");
  klee_make_symbolic(&p10, sizeof(int), "p10");
  klee_make_symbolic(&p11, sizeof(int), "p11");
  klee_make_symbolic(&p12, sizeof(int), "p12");
  klee_make_symbolic(&p13, sizeof(int), "p13");
  klee_make_symbolic(&p14, sizeof(int), "p14");
  klee_make_symbolic(&p15, sizeof(int), "p15");
  klee_make_symbolic(&p16, sizeof(int), "p16");
  klee_make_symbolic(&p17, sizeof(int), "p17");
  klee_make_symbolic(&p18, sizeof(int), "p18");
  klee_make_symbolic(&p19, sizeof(int), "p19");
  klee_make_symbolic(&p20, sizeof(int), "p20");
  klee_make_symbolic(&p21, sizeof(int), "p21");
  klee_make_symbolic(&p22, sizeof(int), "p22");
  klee_make_symbolic(&p23, sizeof(int), "p23");
  klee_make_symbolic(&p24, sizeof(int), "p24");
  klee_make_symbolic(&p25, sizeof(int), "p25");
  klee_make_symbolic(&p26, sizeof(int), "p26");
  klee_make_symbolic(&p27, sizeof(int), "p27");
  klee_make_symbolic(&p28, sizeof(int), "p28");
  klee_make_symbolic(&p29, sizeof(int), "p29");
  klee_make_symbolic(&p30, sizeof(int), "p30");
  klee_make_symbolic(&p31, sizeof(int), "p31");
  klee_make_symbolic(&p32, sizeof(int), "p32");
  klee_make_symbolic(&p33, sizeof(int), "p33");
  klee_make_symbolic(&p34, sizeof(int), "p34");
  klee_make_symbolic(&p35, sizeof(int), "p35");
  klee_make_symbolic(&p36, sizeof(int), "p36");
  klee_make_symbolic(&p37, sizeof(int), "p37");
  klee_make_symbolic(&p38, sizeof(int), "p38");
  klee_make_symbolic(&p39, sizeof(int), "p39");
  klee_make_symbolic(&p40, sizeof(int), "p40");
#endif

  if (p1) {
    wcet += 1;
  } else {
    wcet += 2;
  }
  if (p2) {
    wcet += 3;
  } else {
    wcet += 4;
  }
  if (p3) {
    wcet += 5;
  } else {
    wcet += 6;
  }
  if (p4) {
    wcet += 7;
  } else {
    wcet += 8;
  }
  if (p5) {
    wcet += 9;
  } else {
    wcet += 10;
  }
  if (p6) {
    wcet += 11;
  } else {
    wcet += 12;
  }
  if (p7) {
    wcet += 13;
  } else {
    wcet += 14;
  }
  if (p8) {
    wcet += 15;
  } else {
    wcet += 16;
  }
  if (p9) {
    wcet += 17;
  } else {
    wcet += 18;
  }
  if (p10) {
    wcet += 19;
  } else {
    wcet += 20;
  }
  if (p11) {
    wcet += 21;
  } else {
    wcet += 22;
  }
  if (p12) {
    wcet += 23;
  } else {
    wcet += 24;
  }
  if (p13) {
    wcet += 25;
  } else {
    wcet += 26;
  }
  if (p14) {
    wcet += 27;
  } else {
    wcet += 28;
  }
  if (p15) {
    wcet += 29;
  } else {
    wcet += 30;
  }
  if (p16) {
    wcet += 31;
  } else {
    wcet += 32;
  }
  if (p17) {
    wcet += 33;
  } else {
    wcet += 34;
  }
  if (p18) {
    wcet += 35;
  } else {
    wcet += 36;
  }
  if (p19) {
    wcet += 37;
  } else {
    wcet += 38;
  }
  if (p20) {
    wcet += 39;
  } else {
    wcet += 40;
  }
  if (p21) {
    wcet += 41;
  } else {
    wcet += 42;
  }
  if (p22) {
    wcet += 43;
  } else {
    wcet += 44;
  }
  if (p23) {
    wcet += 45;
  } else {
    wcet += 46;
  }
  if (p24) {
    wcet += 47;
  } else {
    wcet += 48;
  }
  if (p25) {
    wcet += 49;
  } else {
    wcet += 50;
  }
  if (p26) {
    wcet +=51;
  } else {
    wcet += 52;
  }
  if (p27) {
    wcet += 53;
  } else {
    wcet += 54;
  }
  if (p28) {
    wcet += 55;
  } else {
    wcet += 56;
  }
  if (p29) {
    wcet += 57;
  } else {
    wcet += 58;
  }
  if (p30) {
    wcet += 59;
  } else {
    wcet += 60;
  }
  if (p31) {
    wcet += 61;
  } else {
    wcet += 62;
  }
  if (p32) {
    wcet += 63;
  } else {
    wcet += 64;
  }
  if (p33) {
    wcet += 65;
  } else {
    wcet += 66;
  }
  if (p34) {
    wcet += 67;
  } else {
    wcet += 68;
  }
  if (p35) {
    wcet += 69;
  } else {
    wcet += 70;
  }
  if (p36) {
    wcet += 71;
  } else {
    wcet += 72;
  }
  if (p37) {
    wcet += 73;
  } else {
    wcet += 74;
  }
  if (p38) {
    wcet += 75;
  } else {
    wcet += 76;
  }
  if (p39) {
    wcet += 77;
  } else {
    wcet += 78;
  }
  if (p40) {
    wcet += 79;
  } else {
    wcet += 80;
  }

  // wcet should be in _bound
#ifdef LLBMC
    __llbmc_assert(wcet < _bound+1650);
#else
  tracerx_check(wcet);
#endif


}

