/*
 * Copyright 2017 National University of Singapore
 *
 */
#define LLBMC 1
#ifdef LLBMC
#include "llbmc.h"
#else
#include <klee/klee.h>
#endif
int wcet;

int main() {
wcet = 0;
  char b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10;
  char b11,b12,b13,b14,b15,b16,b17,b18,b19,b20;
  char b21,b22,b23,b24,b25,b26,b27,b28,b29,b30;
  char b31,b32,b33,b34,b35,b36,b37,b38,b39,b40;
  char b41,b42,b43,b44,b45,b46,b47,b48,b49,b50;
  
  int x0,x1,x2,x3,x4,x5,x6,x7,x8,x9;
  int x10,x11,x12,x13,x14,x15,x16,x17,x18,x19;
  int x20,x21,x22,x23,x24,x25,x26,x27,x28,x29;  
  int x30,x31,x32,x33,x34,x35,x36,x37,x38,x39;
  int x40,x41,x42,x43,x44,x45,x46,x47,x48,x49;
  int BOUND = 50;

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
  b10 = __llbmc_nondef_char();
  b11 = __llbmc_nondef_char();
  b12 = __llbmc_nondef_char();
  b13 = __llbmc_nondef_char();
  b14 = __llbmc_nondef_char();
  b15 = __llbmc_nondef_char();
  b16 = __llbmc_nondef_char();
  b17 = __llbmc_nondef_char();
  b18 = __llbmc_nondef_char();
  b19 = __llbmc_nondef_char();
  b20 = __llbmc_nondef_char();
  b21 = __llbmc_nondef_char();
  b22 = __llbmc_nondef_char();
  b23 = __llbmc_nondef_char();
  b24 = __llbmc_nondef_char();
  b25 = __llbmc_nondef_char();
  b26 = __llbmc_nondef_char();
  b27 = __llbmc_nondef_char();
  b28 = __llbmc_nondef_char();
  b29 = __llbmc_nondef_char();
  b30 = __llbmc_nondef_char();
  b31 = __llbmc_nondef_char();
  b32 = __llbmc_nondef_char();
  b33 = __llbmc_nondef_char();
  b34 = __llbmc_nondef_char();
  b35 = __llbmc_nondef_char();
  b36 = __llbmc_nondef_char();
  b37 = __llbmc_nondef_char();
  b38 = __llbmc_nondef_char();
  b39 = __llbmc_nondef_char();
  b40 = __llbmc_nondef_char();
  b41 = __llbmc_nondef_char();
  b42 = __llbmc_nondef_char();
  b43 = __llbmc_nondef_char();
  b44 = __llbmc_nondef_char();
  b45 = __llbmc_nondef_char();
  b46 = __llbmc_nondef_char();
  b47 = __llbmc_nondef_char();
  b48 = __llbmc_nondef_char();
  b49 = __llbmc_nondef_char();

  if (b0 > 0) x0 = 0; else x0 = 1;
  if (b1 > 0) x1 = 0; else x1 = 1;
  if (b2 > 0) x2 = 0; else x2 = 1;
  if (b3 > 0) x3 = 0; else x3 = 1;
  if (b4 > 0) x4 = 0; else x4 = 1;    
  if (b5 > 0) x5 = 0; else x5 = 1;
  if (b6 > 0) x6 = 0; else x6 = 1;
  if (b7 > 0) x7 = 0; else x7 = 1;
  if (b8 > 0) x8 = 0; else x8 = 1;
  if (b9 > 0) x9 = 0; else x9 = 1;      
  if (b10 > 0) x10 = 0; else x10 = 1;
  if (b11 > 0) x11 = 0; else x11 = 1;
  if (b12 > 0) x12 = 0; else x12 = 1;
  if (b13 > 0) x13 = 0; else x13 = 1;
  if (b14 > 0) x14 = 0; else x14 = 1;    
  if (b15 > 0) x15 = 0; else x15 = 1;
  if (b16 > 0) x16 = 0; else x16 = 1;
  if (b17 > 0) x17 = 0; else x17 = 1;
  if (b18 > 0) x18 = 0; else x18 = 1;
  if (b19 > 0) x19 = 0; else x19 = 1;      
  if (b20 > 0) x20 = 0; else x20 = 1;
  if (b21 > 0) x21 = 0; else x21 = 1;
  if (b22 > 0) x22 = 0; else x22 = 1;
  if (b23 > 0) x23 = 0; else x23 = 1;
  if (b24 > 0) x24 = 0; else x24 = 1;    
  if (b25 > 0) x25 = 0; else x25 = 1;
  if (b26 > 0) x26 = 0; else x26 = 1;
  if (b27 > 0) x27 = 0; else x27 = 1;
  if (b28 > 0) x28 = 0; else x28 = 1;
  if (b29 > 0) x29 = 0; else x29 = 1;      
  if (b30 > 0) x30 = 0; else x30 = 1;
  if (b31 > 0) x31 = 0; else x31 = 1;
  if (b32 > 0) x32 = 0; else x32 = 1;
  if (b33 > 0) x33 = 0; else x33 = 1;
  if (b34 > 0) x34 = 0; else x34 = 1;    
  if (b35 > 0) x35 = 0; else x35 = 1;
  if (b36 > 0) x36 = 0; else x36 = 1;
  if (b37 > 0) x37 = 0; else x37 = 1;
  if (b38 > 0) x38 = 0; else x38 = 1;
  if (b39 > 0) x39 = 0; else x39 = 1; 
  if (b40 > 0) x40 = 0; else x40 = 1;
  if (b41 > 0) x41 = 0; else x41 = 1;
  if (b42 > 0) x42 = 0; else x42 = 1;
  if (b43 > 0) x43 = 0; else x43 = 1;
  if (b44 > 0) x44 = 0; else x44 = 1;    
  if (b45 > 0) x45 = 0; else x45 = 1;
  if (b46 > 0) x46 = 0; else x46 = 1;
  if (b47 > 0) x47 = 0; else x47 = 1;
  if (b48 > 0) x48 = 0; else x48 = 1;
  if (b49 > 0) x49 = 0; else x49 = 1;           

  tracerx_check();
  return 0;
}
