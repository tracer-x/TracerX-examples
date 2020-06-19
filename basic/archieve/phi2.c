#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <klee/klee.h>


int test(int *a, int *b){
   *a = 5;
   *b = 6;
   return 0;    
}

int main(int argc, char **argv) {

  int a = 1;
  int b = 2;
  unsigned c,d,e;
  klee_make_symbolic(&c, sizeof(unsigned), "c");
  klee_make_symbolic(&d, sizeof(unsigned), "d");
  klee_make_symbolic(&e, sizeof(unsigned), "e");

  if(e) {  printf("arguments provided A are: %d\n",a);}
  else  {  printf("arguments provided B are: %d\n",a);}

  if(d) {  printf("Sajjad1\n");}
  else  {  printf("Sajjad2\n");}
 
  if(!d) {  printf("Sajjad3\n");}
  else  {  test(&a,&b); printf("Sajjad4\n");}
  


  if (a == 5)   printf("a: %d\n",a);
  return 0;


}
