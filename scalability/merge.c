/*
 * From Williams et al.: "PathCrawler: Automatic Generation of Path
 * Tests by Combining Static and Dynamic Analysis", with added KLEE
 * and LLBMC harness.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#define INPUT_SIZE 10

void merge (int t1[],int t2[],int t3[],int l1,int l2){
  int i = 0;
  int j = 0;
  int k = 0;
  while (i < l1 && j < l2) {
    if (t1[i] < t2[j]) {
      t3[k] = t1[i];
      i++; }
    else {
      t3[k] = t2[j];
      j++; }
    k++; }
  while (i < l1) {
    t3[k] = t1[i];
    i++;
    k++; }
  while (j < l2) {
    t3[k] = t2[j];
    j++;
    k++; }
}

int main(int argc, char **argv) {
  int t1[INPUT_SIZE], t2[INPUT_SIZE], t3[INPUT_SIZE + INPUT_SIZE];

#ifdef LLBMC
  for (int i = 0; i < INPUT_SIZE; ++i) {
    t1[i] = __llbmc_nondef_int();
    t2[i] = __llbmc_nondef_int();
    t3[i] = __llbmc_nondef_int();
  }
  for (int i = INPUT_SIZE; i < INPUT_SIZE + INPUT_SIZE; ++i) {
    t3[i] = __llbmc_nondef_int();
  }
#else
  klee_make_symbolic(t1, INPUT_SIZE * sizeof(int), "t1");
  klee_make_symbolic(t2, INPUT_SIZE * sizeof(int), "t2");
  klee_make_symbolic(t3, (INPUT_SIZE + INPUT_SIZE) * sizeof(int), "t3");
#endif

  merge(t1, t2, t3, INPUT_SIZE, INPUT_SIZE);
  return 0;
}
