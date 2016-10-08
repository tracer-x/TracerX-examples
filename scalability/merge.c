/*
 * From Williams et al.: "PathCrawler: Automatic Generation of Path
 * Tests by Combining Static and Dynamic Analysis", with added KLEE
 * harness.
 */

#include <klee/klee.h>

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

  klee_make_symbolic(t1, INPUT_SIZE * sizeof(int), "t1");
  klee_make_symbolic(t2, INPUT_SIZE * sizeof(int), "t2");
  klee_make_symbolic(t3, (INPUT_SIZE + INPUT_SIZE) * sizeof(int), "t3");

  merge(t1, t2, t3, INPUT_SIZE, INPUT_SIZE);
  return 0;
}
