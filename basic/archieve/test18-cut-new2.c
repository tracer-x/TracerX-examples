//This program is pals_floodmax.3_false-unreach-call.1.ufo.BOUNDED-6.pals_true-termination.c
#include<stdio.h>
#include <klee/klee.h>
int kappa;
typedef int bool;
#define true 1
#define false 0
char r1, r2, r3;
bool ep12, ep13, ep21, ep23, ep31, ep32, mode1, mode2, mode3;
 node1() { 
  if (mode1) {
    r1 = (char )((int )r1 + 1);} 
  else {
    if ((int )r1 < 2) {
      if (ep12) {         kappa++; //This lcoation also missed by TX and covered by KLEE.
      }
      if (ep13) { } }}}
 node2() 
{ 
   if (mode2) {
    r2 = (char )((int )r2 + 1);
    if (ep12) {
     }
    if (ep32) { }
    if ((int )r2 == 2) { }} 
    if ((int )r2 < 2) {
      if (ep21) { }      
      if (ep23) { }}}
 node3() 
{ 
  if (mode3) {
    r3 = (char )((int )r3 + 1);
  } else {
    if ((int )r3 < 2) {
      if (ep31) { }
      if (ep32) { }
    } }}
int init() 
{ 
  bool r121=ep12 ;
  bool r211=ep21 ;
  bool r311=ep31 ;
  if (r121) { } 
  if (r211) { } 
  if (r311) { } }
int check() { 
  int tmp ;//Important lines can't remove
  if ((int )r1 >= 2) { } 
  if ((int )r1 < 2) { }  
  return (tmp);}
int main() 
{ 
kappa = 0;
  klee_make_symbolic(&ep12, sizeof(bool), "ep12");
  klee_make_symbolic(&ep13, sizeof(bool), "ep13");
  klee_make_symbolic(&ep21, sizeof(bool), "ep21");
  klee_make_symbolic(&ep23, sizeof(bool), "ep23");
  klee_make_symbolic(&ep31, sizeof(bool), "ep31");
  klee_make_symbolic(&ep32, sizeof(bool), "ep32");
  klee_make_symbolic(&r1, sizeof(char), "r1");
  klee_make_symbolic(&mode1, sizeof(bool), "mode1");
  klee_make_symbolic(&r2, sizeof(char), "r2");
  klee_make_symbolic(&mode2, sizeof(bool), "mode2");
  klee_make_symbolic(&r3, sizeof(char), "r3");
  klee_make_symbolic(&mode3, sizeof(bool), "mode3");
  init();
  node1();
  node2();
  node3();
  check();    
klee_assert(kappa == 0);
return 0;
}

