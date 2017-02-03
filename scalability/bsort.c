/*
 * Another version of bubble sort
 *
 * From Williams et al.: "PathCrawler: Automatic Generation of Path
 * Tests by Combining Static and Dynamic Analysis," with added LLBMC
 * and KLEE harness.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define INPUT_SIZE 9

void bsort (int * tableau, int l)
{
  int i, temp, nb;
  char fini;
  fini = 0;
  nb = 0;
  while ( !fini && (nb < l-1)){
    fini = 1;
    for (i=0 ; i<l-1 ; i++)
      if (tableau[i] < tableau[i+1]){
	fini = 0;
	temp = tableau[i];
	tableau[i] = tableau[i + 1];
	tableau[i + 1] = temp;
      }
    nb++;
  }
}

int main(int argc, char **argv) {
  int tableau[INPUT_SIZE];
#ifdef LLBMC
  for (int i = 0; i < INPUT_SIZE; ++i) {
    tableau[i] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(tableau, INPUT_SIZE * sizeof(int), "tableau");
#endif
  bsort(tableau, INPUT_SIZE);
  return 0;
}
