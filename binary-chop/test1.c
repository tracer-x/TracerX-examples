//This program is psyco_security_true-unreach-call_false-termination.c
#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define BOUND 10

// method ids
int m_initSign = 1;
int m_initVerify = 2;
int m_Signature = 3;
int m_sign = 4;
int m_verify = 5;
int m_update = 6;
 
int kappa;
int main() 
{
kappa =0;
int dummy = 1;
  int q=0, FLAG=0, i=0;
  // klee_make_symbolic(&q, sizeof(int), "q");
  int method_id;

  // variables
    int this_state=0;
	// klee_make_symbolic(&this_state, sizeof(int), "this_state");

   int symb[BOUND][22];
   klee_make_symbolic(symb, sizeof(int) * BOUND * 22, "symb");

  for (int FLAG=0;FLAG<BOUND;FLAG++) {
     //printf("\n\n*****Loop Iteration:= %d (q = %d) *****\n\n",FLAG, q);

    // parameters
        
    // states
        if (q == 0){      
                
                if(symb[FLAG][1]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    this_state=0; 
                  }
                  continue;
                }

          continue;
        }
        if (q == 1){      
                
                if(symb[FLAG][2]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( this_state == 2 ) {
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
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( this_state == 3 ) {
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
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( (((this_state == 2) && (this_state != 3)) || (this_state == 3)) ) {
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
               
                if(symb[FLAG][5]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=2; 
                  }
                  continue;
                }
               
                if(symb[FLAG][6]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=3; 
                  }
                  continue;
                }
               
                if(symb[FLAG][7]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( this_state == 2 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(symb[FLAG][8]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( this_state == 3 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(symb[FLAG][9]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( (((this_state == 2) && (this_state != 3)) || (this_state == 3)) ) {
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
        if (q == 3){      
       
                if(symb[FLAG][10]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=2; 
                  }
                  continue;
                }
              
                if(symb[FLAG][11]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=3; 
                  }
                  continue;
                }
                
                if(symb[FLAG][12]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (this_state != 2) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }
               
                if(symb[FLAG][13]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (this_state == 3) ) {
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
                  if ( (dummy  ==  1) && (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }
                
                if(symb[FLAG][15]){
                  // assume guard
                  if ( (dummy  ==  1) && (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3)))&& ((this_state == 3) || ((this_state != 2) && (this_state != 3))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }

          continue;
        }
        if (q == 4){      
       
                if(symb[FLAG][16]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=2; 
                  }
                  continue;
                }
                
                if(symb[FLAG][17]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=3; 
                  }
                  continue;
                }
                
                if(symb[FLAG][18]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (this_state == 2) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
              
                if(symb[FLAG][19]){
                  // assume guard
                  if ( dummy  ==  1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (this_state != 3) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }
               
                if(symb[FLAG][20]){
                  // assume guard
                  if ( (dummy  ==  1) && (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }
               
                if(symb[FLAG][21]){
                  // assume guard
                  if ( (dummy  ==  1) && (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3)))&& ((this_state == 3) || ((this_state != 2) && (this_state != 3))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=this_state; 
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
