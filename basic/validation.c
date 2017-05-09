/*
 * Password validation code from
 * https://gitlab.com/Manouchehri/Matryoshka-Stage-2/blob/master/stage2.md
 * with instrumentation for generating symbolic inputs added. KLEE
 * produces the hardcoded password "Pandi_panda" when klee_assert(0)
 * is visited.
 *
 * Portions copyright 2017 National University of Singapore
 */
#include <stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <assert.h>
#include <klee/klee.h>
#endif

/*--- Added strlen so we don't need uclibc --*/
size_t strlen(const char *s) {
  const char *t = s;
  while (*s++);
  return (size_t) (s - t - 1);
}

int main(int a1, char **a2, char **a3)
{
  __int64_t v4; // rbx@10
  signed int v5; // [sp+1Ch] [bp-14h]@4

  /*--------------- Added code ----------------*/
  char input[100];
#ifdef LLBMC
  for (size_t i = 0; i < 100; i++) {
    input[i] = __llbmc_nondef_char();
  }
#else
  klee_make_symbolic(input, 100 * sizeof(char), "input");
#endif
  a2[1] = input;
  a1 = 2;
  /*-------------- End Added code -------------*/
  
  if ( a1 == 2 )
  {
    if ( 42 * (strlen(a2[1]) + 1) != 504 )
      goto LABEL_31;
    v5 = 1;
    if ( *a2[1] != 80 )
      v5 = 0;
    if ( 2 * a2[1][3] != 200 )
      v5 = 0;
    if ( *a2[1] + 16 != a2[1][6] - 16 )
      v5 = 0;
    v4 = a2[1][5];
    if ( v4 != 9 * strlen(a2[1]) - 4 )
      v5 = 0;
    if ( a2[1][1] != a2[1][7] )
      v5 = 0;
    if ( a2[1][1] != a2[1][10] )
      v5 = 0;
    if ( a2[1][1] - 17 != *a2[1] )
      v5 = 0;
    if ( a2[1][3] != a2[1][9] )
      v5 = 0;
    if ( a2[1][4] != 105 )
      v5 = 0;
    if ( a2[1][2] - a2[1][1] != 13 )
      v5 = 0;
    if ( a2[1][8] - a2[1][7] != 13 )
      v5 = 0;
    if ( v5 ) {
      printf("Good good!\n");
#ifdef LLBMC
      __llbmc_assert(0);
#else
      klee_assert(0);
#endif
    }
    else
LABEL_31:
      printf("Try again...\n");
  }
  else
  {
    printf("Usage: %s <pass>\n", *a2);
  }
}
