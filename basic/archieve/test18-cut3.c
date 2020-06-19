//This program is pals_floodmax.3_false-unreach-call.1.ufo.BOUNDED-6.pals_true-termination.c
#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif


int kappa;
typedef int bool;
#define true 1
#define false 0
 assert(bool arg ) ;

typedef char msg_t;
typedef int port_t;
extern void read(port_t p , msg_t m ) ;
extern void write(port_t p , msg_t m ) ;
msg_t nomsg  =    (msg_t )-1;
port_t p12  ;
char p12_old ;
char p12_new ;
bool ep12  ;
port_t p13  ;
char p13_old ;
char p13_new ;
bool ep13  ;
port_t p21  ;
char p21_old ;
char p21_new ;
bool ep21  ;
port_t p23  ;
char p23_old ;
char p23_new ;
bool ep23  ;
port_t p31  ;
char p31_old ;
char p31_new ;
bool ep31  ;
port_t p32  ;
char p32_old ;
char p32_new ;
bool ep32  ;
char id1  ;
char r1  ;
char st1  ;
char nl1  ;
char m1  ;
char max1  ;
bool mode1  ;
char id2  ;
char r2  ;
char st2  ;
char nl2  ;
char m2  ;
char max2  ;
bool mode2  ;
char id3  ;
char r3  ;
char st3  ;
char nl3  ;
char m3  ;
char max3  ;
bool mode3  ;
 node1() 
{ 


  {
  if (mode1) {
    r1 = (char )((int )r1 + 1);
    if (ep21) {
      m1 = p21_old;
      p21_old = nomsg;
      if ((int )m1 > (int )max1) {
        max1 = m1;
      }
    }
    if (ep31) {
      m1 = p31_old;
      p31_old = nomsg;
      if ((int )m1 > (int )max1) {
        max1 = m1;
      }
    }
    if ((int )r1 == 2) {
      if ((int )max1 == (int )id1) {
        st1 = (char)1;
      } else {
        nl1 = (char)1;
      }
    }
    mode1 = (bool)0;
  } else {
    if ((int )r1 < 2) {
      if (ep12) {
        
        
        if ((max1 != nomsg) && (p12_new == nomsg))
        {
        p12_new = max1;
        }
        else
        {
        p12_new = p12_new;
        }
      }
      if (ep13) {
        
      
      if ((max1 != nomsg) && (p13_new == nomsg))
        {
        p13_new = max1;
        }
        else
        {
        p13_new = p13_new;
        }
      
      }
    }
    mode1 = (bool)1;
  }
  
}
}
 node2() 
{ 


  {
  if (mode2) {
    r2 = (char )((int )r2 + 1);
    if (ep12) {
      m2 = p12_old;
      p12_old = nomsg;
      if ((int )m2 > (int )max2) {
        max2 = m2;
        kappa++;//This lcoation also missed by TX and covered by KLEE
      }
    }
    if (ep32) {
      m2 = p32_old;
      p32_old = nomsg;
      if ((int )m2 > (int )max2) {
        max2 = m2;
        //This lcoation also missed by TX and covered by KLEE
      }
    }
    if ((int )r2 == 2) {
      if ((int )max2 == (int )id2) {
        st2 = (char)1;
      } else {
        nl2 = (char)1;
      }
    }
    mode2 = (bool)0;
  } else {
    if ((int )r2 < 2) {
      if (ep21) {


      
      if ((max2 != nomsg) && (p21_new == nomsg))
        {
        p21_new = max2;
        }
        else
        {
        p21_new = p21_new;
        }
        }      
      
      if (ep23) {
        
      
      if ((max2 != nomsg) && (p23_new == nomsg))
        {
        p23_new = max2;
        }
        else
        {
        p23_new = p23_new;
        }
        
      }  
    }
    mode2 = (bool)1;
  }
  
}
}
// *nodes[3]  = {      & node1,      & node2,      & node3};
  *nodes[2]  = {& node1,& node2};
int init() 
{ 
  bool r121 ;
  bool r131 ;
  bool r211 ;
  bool r231 ;
  bool r311 ;
  bool r321 ;
  bool r122 ;
  int tmp ;
  bool r132 ;
  int tmp___0 ;
  bool r212 ;
  int tmp___1 ;
  bool r232 ;
  int tmp___2 ;
  bool r312 ;
  int tmp___3 ;
  bool r322 ;
  int tmp___4 ;
  int tmp___5 ;

  {
  r121 = ep12;
  r131 = ep13;
  r211 = ep21;
  r231 = ep23;
  r311 = ep31;
  r321 = ep32;
  if (r121) {
    tmp = 1;
  } else
  if (r131) {
    if (ep32) {
      tmp = 1;
    } else {
      tmp = 0;
    }
  } else {
    tmp = 0;
  }
  r122 = (bool )tmp;
  if (r131) {
    tmp___0 = 1;
  } else
  if (r121) {
    if (ep23) {
      tmp___0 = 1;
    } else {
      tmp___0 = 0;
    }
  } else {
    tmp___0 = 0;
  }
  r132 = (bool )tmp___0;
  if (r211) {
    tmp___1 = 1;
  } else
  if (r231) {
    if (ep31) {
      tmp___1 = 1;
    } else {
      tmp___1 = 0;
    }
  } else {
    tmp___1 = 0;
  }
  r212 = (bool )tmp___1;
  if (r231) {
    tmp___2 = 1;
  } else
  if (r211) {
    if (ep13) {
      tmp___2 = 1;
    } else {
      tmp___2 = 0;
    }
  } else {
    tmp___2 = 0;
  }
  r232 = (bool )tmp___2;
  if (r311) {
    tmp___3 = 1;
  } else
  if (r321) {
    if (ep21) {
      tmp___3 = 1;

    } else {
      tmp___3 = 0;
    }
  } else {
    tmp___3 = 0;

  }
  r312 = (bool )tmp___3;
  if (r321) {
    tmp___4 = 1;
  } else
  if (r311) {
    if (ep12) {
      tmp___4 = 1;
    } else {
      tmp___4 = 0;
    }
  } else {
    tmp___4 = 0;
   
  }
 
}
}
int check() 
{ 
  int tmp ;

  {
  if (((int )st1 + (int )st2) + (int )st3 <= 1) {
    if ((int )st1 + (int )nl1 <= 1) {
      if ((int )st2 + (int )nl2 <= 1) {
        if ((int )st3 + (int )nl3 <= 1) {
          if ((int )r1 >= 2) {
            goto _L___1;
          } else
          if (((int )st1 + (int )st2) + (int )st3 == 0) {
            _L___1: /* CIL Label */ 
            if ((int )r1 < 2) {
              goto _L___0;
            } else
            if (((int )st1 + (int )st2) + (int )st3 == 1) {
              _L___0: /* CIL Label */ 
              if ((int )r1 >= 2) {
                goto _L;
              } else
              if (((int )nl1 + (int )nl2) + (int )nl3 == 0) {
                _L: /* CIL Label */ 
                if ((int )r1 < 2) {
                  tmp = 1;
                } else
                if (((int )nl1 + (int )nl2) + (int )nl3 == 2) {
                  tmp = 1;
                } else {
                  tmp = 0;
                }
              } else {
                tmp = 0;
              }
            } else {
              tmp = 0;

            }
          } else {
            tmp = 0;
          }
        } else {
          tmp = 0;
        }
      } else {
        tmp = 0;
      }
    } else {
      tmp = 0;
    }
  } else {
    tmp = 0;
  }
  return (tmp);
}
}

 

int main() 
{ 
kappa = 0;
  int c1 ;
  int i2 ;

  {
  c1 = 0;

  
  klee_make_symbolic(&ep12, sizeof(bool), "ep12");
  klee_make_symbolic(&ep13, sizeof(bool), "ep13");
  klee_make_symbolic(&ep21, sizeof(bool), "ep21");
  klee_make_symbolic(&ep23, sizeof(bool), "ep23");
  klee_make_symbolic(&ep31, sizeof(bool), "ep31");
  klee_make_symbolic(&ep32, sizeof(bool), "ep32");
  
  klee_make_symbolic(&id1, sizeof(char), "id1");
  klee_make_symbolic(&r1, sizeof(char), "r1");
  klee_make_symbolic(&st1, sizeof(char), "st1");
  klee_make_symbolic(&nl1, sizeof(char), "nl1");
    klee_make_symbolic(&m1, sizeof(char), "m1");
  klee_make_symbolic(&max1, sizeof(char), "max1");
  
  klee_make_symbolic(&mode1, sizeof(bool), "mode1");
  klee_make_symbolic(&id2, sizeof(char), "id2");
  klee_make_symbolic(&r2, sizeof(char), "r2");
  klee_make_symbolic(&st2, sizeof(char), "st2");
  klee_make_symbolic(&nl2, sizeof(char), "nl2");
  klee_make_symbolic(&m2, sizeof(char), "m2");
  
  klee_make_symbolic(&max2, sizeof(char), "max2");
  klee_make_symbolic(&mode2, sizeof(bool), "mode2");
  
    
  i2 = init();
  p12_old = nomsg;
  p12_new = nomsg;
  p13_old = nomsg;
  p13_new = nomsg;
  p21_old = nomsg;
  p21_new = nomsg;
  p23_old = nomsg;
  p23_new = nomsg;

i2 = 0;  
  while (i2 < 1) {
    {
    node1();
    node2();
    
    p12_old = p12_new;
    p12_new = nomsg;
    p13_old = p13_new;
    p13_new = nomsg;
    p21_old = p21_new;
    p21_new = nomsg;
    p23_old = p23_new;
    p23_new = nomsg;
    
    c1 = check();
   
    i2++;
    }
  }
}
klee_assert(kappa == 0);
return 0;
}

