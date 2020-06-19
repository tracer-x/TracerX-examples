#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <klee/klee.h>



int main(int argc, char **argv) {

  printf("arguments provided are: %d\n",argc);
  if (argc == 1)   printf("argc: %d\n",argc);  
  if (argc == 2)   printf("argc: %d\n",argc);
  if (argc == 3)   printf("argc: %d\n",argc);  
  return 0;


}
