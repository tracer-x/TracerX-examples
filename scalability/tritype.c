/* 
 * From Williams et al.: "PathCrawler: Automatic Generation of Path
 * Tests by Combining Static and Dynamic Analysis," with added KLEE
 * harness.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int tritype(int i, int j, int k){
  int trityp;
  if ((i == 0) || (j == 0) || (k == 0)) trityp = 4;
  else {
    trityp = 0;
    if (i == j) trityp = trityp + 1;
    if (i == k) trityp = trityp + 2;
    if (j == k) trityp = trityp + 3;
    if (trityp == 0){
      if ((i+j <= k) || (j+k <= i) || (i+k <= j)) trityp = 4;
      else trityp = 1;
    }
    else if (trityp > 3) trityp = 3;
    else if ((trityp == 1) && (i+j > k)) trityp = 2;
    else if ((trityp == 2) && (i+k > j)) trityp = 2;
    else if ((trityp == 3) && (j+k > i)) trityp = 2;
    else trityp = 4;
  }
  return trityp;
}

int main(int argc, char **argv) {
  int i, j, k;

#ifdef LLBMC
  i = __llbmc_nondef_int();
  j = __llbmc_nondef_int();
  k = __llbmc_nondef_int();
#else
  klee_make_symbolic(&i, sizeof(i), "i");
  klee_make_symbolic(&j, sizeof(j), "j");
  klee_make_symbolic(&k, sizeof(k), "k");
#endif

  tritype(i, j, k);
  return 0;
}
