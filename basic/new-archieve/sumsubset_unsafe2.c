/*
 * Copyright 2017 National University of Singapore
 *
 */
#include <stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main(int argc, char **argv) {
  char b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10;
  char b11,b12,b13,b14,b15,b16,b17,b18,b19,b20;
  char b21,b22,b23,b24,b25,b26,b27,b28,b29,b30;
  char b31,b32,b33,b34,b35,b36,b37,b38,b39,b40;
  char b41,b42,b43,b44,b45,b46,b47,b48,b49,b50;
  
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
  klee_make_symbolic(&b10, sizeof(char), "b10");
  

  klee_make_symbolic(&b11, sizeof(char), "b11");
  klee_make_symbolic(&b12, sizeof(char), "b12");
  klee_make_symbolic(&b13, sizeof(char), "b13");
  klee_make_symbolic(&b14, sizeof(char), "b14");
  klee_make_symbolic(&b15, sizeof(char), "b15");
  klee_make_symbolic(&b16, sizeof(char), "b16");
  klee_make_symbolic(&b17, sizeof(char), "b17");
  klee_make_symbolic(&b18, sizeof(char), "b18");
  klee_make_symbolic(&b19, sizeof(char), "b19");
  klee_make_symbolic(&b20, sizeof(char), "b20");
  

  klee_make_symbolic(&b21, sizeof(char), "b21");
  klee_make_symbolic(&b22, sizeof(char), "b22");
  klee_make_symbolic(&b23, sizeof(char), "b23");
  klee_make_symbolic(&b24, sizeof(char), "b24");
  klee_make_symbolic(&b25, sizeof(char), "b25");
  klee_make_symbolic(&b26, sizeof(char), "b26");
  klee_make_symbolic(&b27, sizeof(char), "b27");
  klee_make_symbolic(&b28, sizeof(char), "b28");
  klee_make_symbolic(&b29, sizeof(char), "b29");
  klee_make_symbolic(&b30, sizeof(char), "b30");
  

  klee_make_symbolic(&b31, sizeof(char), "b31");
  klee_make_symbolic(&b32, sizeof(char), "b32");
  klee_make_symbolic(&b33, sizeof(char), "b33");
  klee_make_symbolic(&b34, sizeof(char), "b34");
  klee_make_symbolic(&b35, sizeof(char), "b35");
  klee_make_symbolic(&b36, sizeof(char), "b36");
  klee_make_symbolic(&b37, sizeof(char), "b37");
  klee_make_symbolic(&b38, sizeof(char), "b38");
  klee_make_symbolic(&b39, sizeof(char), "b39");
  klee_make_symbolic(&b40, sizeof(char), "b40");
  
  

  klee_make_symbolic(&b41, sizeof(char), "b41");
  klee_make_symbolic(&b42, sizeof(char), "b42");
  klee_make_symbolic(&b43, sizeof(char), "b43");
  klee_make_symbolic(&b44, sizeof(char), "b44");
  klee_make_symbolic(&b45, sizeof(char), "b45");
  klee_make_symbolic(&b46, sizeof(char), "b46");
  klee_make_symbolic(&b47, sizeof(char), "b47");
  klee_make_symbolic(&b48, sizeof(char), "b48");
  klee_make_symbolic(&b49, sizeof(char), "b49");
  klee_make_symbolic(&b50, sizeof(char), "b50");
  
  int x = 0;

  if (b0 == 90)
    x += 90;
  else
    x += 0;
  if (b1 == 89)
    x += 75;
  else
    x += 0;
  if (b2 == 88)
    x += 75;
  else
    x += 0;
  if (b3 == 87)
    x += 70;
  else
    x += 0;
  if (b4 == 86)
    x += 115;
  else
    x += 0;
  if (b5 == 85)
    x += 35;
  else
    x += 0;
  if (b6 == 84)
    x += 85;
  else
    x += 0;
  if (b7 == 83)
    x += 55;
  else
    x += 0;
  if (b8 == 82)
    x += 65;
  else
    x += 0;
  if (b9 == 81)
    x += 125;
  else
    x += 0;
  if (b10 == 80)
    x += 125;
  else
    x += 0;
  if (b11 == 79)
    x += 95;
  else
    x += 0;
  if (b12 == 78)
    x += 90;
  else
    x += 0;
  if (b13 == 77)
    x += 105;
  else
    x += 0;
  if (b14 == 76)
    x += 135;
  else
    x += 0;
  if (b15 == 75)
    x += 45;
  else
    x += 1;
  if (b16 == 74)
    x += 110;
  else
    x += 0;
  if (b17 == 73)
    x += 95;
  else
    x += 1;
  if (b18 == 72)
    x += 115;
  else
    x += 0;
  if (b19 == 71)
    x += 145;
  else
    x += 0;  
  /*if (b20 > 0)
    x += 60;
  else
    x += 0;
  if (b21 > 0)
    x += 105;
  else
    x += 0;
  if (b22 > 0)
    x += 80;
  else
    x += 0;
  if (b23 > 0)
    x += 75;
  else
    x += 0;
  if (b24 > 0)
    x += 155;
  else
    x += 0;
  if (b25 > 0)
    x += 45;
  else
    x += 0;
  if (b26 > 0)
    x += 65;
  else
    x += 0;
  if (b27 > 0)
    x += 110;
  else
    x += 0;
  if (b28 > 0)
    x += 95;
  else
    x += 0;
  if (b29 > 0)
    x += 145;
  else
    x += 0;
  if (b30 > 0)
    x += 90;
  else
    x += 0;
  if (b31 > 0)
    x += 75;
  else
    x += 0;
  if (b32 > 0)
    x += 75;
  else
    x += 0;
  if (b33 > 0)
    x += 70;
  else
    x += 0;
  if (b34 > 0)
    x += 135;
  else
    x += 0;
  if (b35 > 0)
    x += 60;
  else
    x += 0;
  if (b36 > 0)
    x += 105;
  else
    x += 0;
  if (b37 > 0)
    x += 80;
  else
    x += 0;
  if (b38 > 0)
    x += 75;
  else
    x += 0;
  if (b39 > 0)
    x += 125;
  else
    x += 0;*/

    
  int BOUND = (90+75+75+70+115
               +35+85+55+65+125
               +125+95+90+105+135
               +1+110+1+115+145
  	       //+60+105+80+75+155
  	       //+45+65+110+95+145
  	       //+90+75+75+70+135
               //+60+105+80+75+125
               );  
 
  
   

  
  klee_assert(x != BOUND);

  return 0;
}
