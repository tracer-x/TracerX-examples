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
 
int wcet;
int UB = 30000;
int B = 30000;
int LB = 20;


int checkArray (int** array,int bound,int offset)
{
    if (bound == 1) return array[1][offset];
    else if (bound == 2) return array[2][offset];
    else if (bound == 3) return array[3][offset];
    else if (bound == 4) return array[4][offset];
    else if (bound == 5) return array[5][offset];
    else if (bound == 6) return array[6][offset];
    else if (bound == 7) return array[7][offset];
    else if (bound == 8) return array[8][offset];
    else if (bound == 9) return array[9][offset];
}


int main() 
{
  wcet =0;
  int dummy = 1;
  int q=0, FLAG=0, i=0;
  wcet+=4;
  // klee_make_symbolic(&q, sizeof(int), "q");
  int method_id;

  // variables
  int this_state=0;
  wcet+=1;
  // klee_make_symbolic(&this_state, sizeof(int), "this_state");

  int symb[BOUND][22];
  klee_make_symbolic(symb, sizeof(int) * BOUND * 22, "symb");

  wcet+=1;
  for (int FLAG=0;FLAG<10;FLAG++) {
  	wcet+=1;        
	if (q == 0){ 
                if(checkArray(symb,FLAG,1)){  wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){   wcet+=1;
                    // record method id
                    method_id = 3;  wcet+=1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {  wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 2;  wcet+=1;
                    // post condition
                    this_state=0;   wcet+=1;
                  }
                  continue;
                }

          continue;
        }
        if (q == 1){      
                wcet+=4;
                if(checkArray(symb,FLAG,2)){   wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){   wcet+=1;
                    // record method id
                    method_id = 4; wcet+=1;
                    // non-conformance condition 
                    if ( this_state == 2 ) { wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 1;wcet+=1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(checkArray(symb,FLAG,3)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 5;wcet+=1;
                    // non-conformance condition 
                    if ( this_state == 3 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 1;wcet+=1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(symbcheckArray(symb,FLAG,4)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 6;wcet+=1;
                    // non-conformance condition 
                    if ( (((this_state == 2) && (this_state != 3)) || (this_state == 3)) ){ 
		      wcet+=3;
                      goto ERROR;
                    }
                    // state update
                    q = 1;wcet+=1;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 2){   wcet+=1;
               
                if(checkArray(symb,FLAG,5)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 1;wcet+=1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 3;wcet+=1;
                    // post condition
                    this_state=2; wcet+=1;
                  }
                  continue;
                }
               
                if(checkArray(symb,FLAG,6)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 2;wcet+=1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 4;wcet+=1;
                    // post condition
                    this_state=3; wcet+=1;
                  }
                  continue;
                }
               
                if(checkArray(symb,FLAG,7)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 4;wcet+=1;
                    // non-conformance condition 
                    if ( this_state == 2 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 1;wcet+=1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(checkArray(symb,FLAG,8)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 5;wcet+=1;
                    // non-conformance condition 
                    if ( this_state == 3 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 1;wcet+=1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(checkArray(symb,FLAG,9)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 6;wcet+=1;
                    // non-conformance condition 
                    if ( (((this_state == 2) && (this_state != 3)) || (this_state == 3)) ) {
			wcet+=3;                      
			goto ERROR;
                    }
                    // state update
                    q = 1;wcet+=1;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 3){      wcet+=1;
       
                if(checkArray(symb,FLAG,10)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 1;wcet+=1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 3;wcet+=1;
                    // post condition
                    this_state=2; wcet+=1;
                  }
                  continue;
                }
              
                if(checkArray(symb,FLAG,11)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 2;wcet+=1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 4;wcet+=1;
                    // post condition
                    this_state=3; wcet+=1;
                  }
                  continue;
                }
                
                if(checkArray(symb,FLAG,12)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 4;wcet+=1;
                    // non-conformance condition 
                    if ( (this_state != 2) ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 3;wcet+=1;
                    // post condition
                    this_state=this_state; wcet+=1;
                  }
                  continue;
                }
               
                if(checkArray(symb,FLAG,13)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 5;wcet+=1;
                    // non-conformance condition 
                    if ( (this_state == 3) ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 1;wcet+=1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(checkArray(symb,FLAG,14)){wcet+=1;
                  // assume guard
                  if ( (dummy  ==  1) && (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3))) ){ wcet+=5;
                    // record method id
                    method_id = 6;wcet+=1;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {wcet+=2;
                      goto ERROR;
                    }
                    // state update
                    q = 3;wcet+=1;
                    // post condition
                    this_state=this_state; wcet+=1;
                  }
                  continue;
                }
                
                if(checkArray(symb,FLAG,15)){wcet+=1;
                  // assume guard
                  if ( (dummy  ==  1) && (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3)))&& ((this_state == 3) || ((this_state != 2) && (this_state != 3))) ){ wcet+=8;
                    // record method id
                    method_id = 6;wcet+=1;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {wcet+=2;
                      goto ERROR;
                    }
                    // state update
                    q = 3;wcet+=1;
                    // post condition
                    this_state=this_state;wcet+=1; 
                  }
                  continue;
                }

          continue;
        }
        if (q == 4){      wcet+=1;
       
                if(checkArray(symb,FLAG,16)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 1;wcet+=1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 3;wcet+=1;
                    // post condition
                    this_state=2; wcet+=1;
                  }
                  continue;
                }
                
                if(checkArray(symb,FLAG,17)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 2;wcet+=1;
                    // non-conformance condition 
                    if ( dummy  !=  1 ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 4;wcet+=1;
                    // post condition
                    this_state=3; wcet+=1;
                  }
                  continue;
                }
                
                if(checkArray(symb,FLAG,18)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 4;wcet+=1;
                    // non-conformance condition 
                    if ( (this_state == 2) ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 1;wcet+=1;
                    // post condition
                    break;
                  }
                  continue;
                }
              
                if(checkArray(symb,FLAG,19)){wcet+=1;
                  // assume guard
                  if ( dummy  ==  1 ){ wcet+=1;
                    // record method id
                    method_id = 5;wcet+=1;
                    // non-conformance condition 
                    if ( (this_state != 3) ) {wcet+=1;
                      goto ERROR;
                    }
                    // state update
                    q = 4;wcet+=1;
                    // post condition
                    this_state=this_state; wcet+=1;
                  }
                  continue;
                }
               
                if(checkArray(symb,FLAG,20)){wcet+=1;
                  // assume guard
                  if ( (dummy  ==  1) && (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3))) ){ wcet+=5;
                    // record method id
                    method_id = 6;wcet+=1;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {wcet+=2;
                      goto ERROR;
                    }
                    // state update
                    q = 4;wcet+=1;
                    // post condition
                    this_state=this_state; wcet+=1;
                  }
                  continue;
                }
               
                if(checkArray(symb,FLAG,21)){wcet+=1;
                  // assume guard
                  if ( (dummy  ==  1) && (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3)))&& ((this_state == 3) || ((this_state != 2) && (this_state != 3))) ){ wcet+=8;
                    // record method id
                    method_id = 6;wcet+=1;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {wcet+=2;
                      goto ERROR;
                    }
                    // state update
                    q = 4;wcet+=1;
                    // post condition
                    this_state=this_state; wcet+=1;
                  }
                  continue;
                }

          continue;
        }
        
   
  
  } // end while

  
 ERROR:
  //printf("error \n ");
 printf("Timing of Path:%d\n",wcet); 
 klee_assert(wcet <= B);
 return 0;
}
