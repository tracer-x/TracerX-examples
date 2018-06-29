//This program is psyco_math_1_true-unreach-call_false-termination.c
#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#define BOUND 10
// method ids
int m_isPowerOfTwo = 1;
int m_IntMath = 2;
int m_log10 = 3;
int m_checkedSubtract = 4;
int m_checkedMultiply = 5;
int m_log2 = 6;
int m_checkedAdd = 7;
int m_mod_1 = 8;
int m_mod_2 = 9;
int m_factorial_1 = 10;
int m_factorial_2 = 11;

int kappa; 

int main() {
kappa = 0;
int dummy = 1;
   int q=0,FLAG=0,i=0;
  int method_id;

  // variables
   
int symb[BOUND][20];
   klee_make_symbolic(symb, sizeof(int) * BOUND * 20, "symb");
 
    // parameters
 

        int P1;
        int P2;
        int P3;
        int P4;
        int P5;
        int P6;
        int P7;
        int P8;
        int P9;
        int P10;
        int P11;
        int P12;
        int P13;
        int P14;
        int P15;
        int P16;
        int P17;
 


        klee_make_symbolic(&P1, sizeof(int), "P1");
        klee_make_symbolic(&P2, sizeof(int), "P2");
        klee_make_symbolic(&P3, sizeof(int), "P3");
        klee_make_symbolic(&P4, sizeof(int), "P4");
        klee_make_symbolic(&P5, sizeof(int), "P5");
        
        klee_make_symbolic(&P6, sizeof(int), "P6");
        klee_make_symbolic(&P7, sizeof(int), "P7");
        klee_make_symbolic(&P8, sizeof(int), "P8");
        klee_make_symbolic(&P9, sizeof(int), "P9");
        
        klee_make_symbolic(&P10, sizeof(int), "P10");
        klee_make_symbolic(&P11, sizeof(int), "P11");
        klee_make_symbolic(&P12, sizeof(int), "P12");
        
        klee_make_symbolic(&P13, sizeof(int), "P13");
        klee_make_symbolic(&P14, sizeof(int), "P14");
        klee_make_symbolic(&P15, sizeof(int), "P15");
        klee_make_symbolic(&P16, sizeof(int), "P16");
        klee_make_symbolic(&P17, sizeof(int), "P17");
        
        
        
        
        for (int FLAG=0;FLAG<BOUND;FLAG++) {
    // printf("\n\n*****Loop Iteration:= %d (q = %d) *****\n\n",FLAG, q);
        
        
        
        
        
        
        
        
        
    // states
        if (q == 0){      
                
                if(symb[FLAG][1]){
                  // assume guard
                  if ( dummy == 1 ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }

          continue;
        }
        if (q == 1){      
               
                if(symb[FLAG][2]){
                  // assume guard
                  if ( dummy == 1 ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(symb[FLAG][3]){
                  // assume guard
                  if ( dummy == 1 ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(symb[FLAG][4]){
                  // assume guard
                  if ( !((P1 >= 0) && (P2 > 0)) ){ 
                    // record method id
                    method_id = 9;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(symb[FLAG][5]){
                  // assume guard
                  if ( (P1 < 0) ){ 
                    // record method id
                    method_id = 10;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 2){      
        
                if(symb[FLAG][6]){
                  // assume guard
                  if ( ( dummy == 1 ) && ((((P1 & (P1 - 1)) == 0) && (P1 > 0)) || ( dummy != 1 )) ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][7]){
                  // assume guard
                  if ( ( dummy == 1 ) && ((((P1 & (P1 - 1)) == 0) && (P1 > 0)) || ( dummy != 1 ))&& ((((P1 & (P1 - 1)) != 0) && (P1 > 0)) || ( dummy != 1 )) ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][8]){
                  // assume guard
                  if ( ( dummy == 1 ) && ((((P1 & (P1 - 1)) == 0) && (P1 > 0)) || ( dummy != 1 ))&& ((((P1 & (P1 - 1)) != 0) && (P1 > 0)) || ( dummy != 1 ))&& ((((P1 & (P1 - 1)) == 0) && (P1 <= 0)) || ( dummy != 1 )) ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][9]){
                  // assume guard
                  if ( ( dummy == 1 ) && ((((P1 & (P1 - 1)) == 0) && (P1 > 0)) || ( dummy != 1 ))&& ((((P1 & (P1 - 1)) != 0) && (P1 > 0)) || ( dummy != 1 ))&& ((((P1 & (P1 - 1)) == 0) && (P1 <= 0)) || ( dummy != 1 ))&& ((((P1 & (P1 - 1)) != 0) && (P1 <= 0)) || ( dummy != 1 )) ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][10]){
                  // assume guard
                  if ( dummy == 1 ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(symb[FLAG][11]){
                  // assume guard
                  if ( dummy == 1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][12]){
                  // assume guard
                  if ( dummy == 1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][13]){
                  // assume guard
                  if ( dummy == 1 ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(symb[FLAG][14]){
                  // assume guard
                  if ( dummy == 1 ){ 
                    // record method id
                    method_id = 7;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][15]){
                  // assume guard
                  if ( ((P1 >= 0) && (P2 > 0)) ){ 
                    // record method id
                    method_id = 8;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][16]){
                  // assume guard
                  if ( !((P1 >= 0) && (P2 > 0)) ){ 
                    // record method id
                    method_id = 9;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(symb[FLAG][17]){
                  // assume guard
                  if ( (P1 < 0) ){ 
                    // record method id
                    method_id = 10;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(symb[FLAG][18]){
                  // assume guard
                  if ( !(P1 < 0)&& (((P17 < 13) && (P17 >= 0)) || ( dummy != 1 )) ){ 
                    // record method id
                    method_id = 11;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }
                
                if(symb[FLAG][19]){
                  // assume guard
                  if ( !(P1 < 0) && (((P17 < 13) && (P17 >= 0)) || ( dummy != 1 ))&& (((P17 >= 13) && (P17 >= 0)) || ( dummy != 1 )) ){ 
                    // record method id
                    method_id = 11;
                    // non-conformance condition 
                    if ( dummy != 1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                  }
                  continue;
                }

          continue;
        }
   

  } // end while

  ERROR:
  //printf("error \n ");


 
 


 


 return 0;
}
