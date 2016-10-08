/* 
 * From Williams et al.: "PathCrawler: Automatic Generation of Path
 * Tests by Combining Static and Dynamic Analysis", with added KLEE
 * harness.
 */

#include <klee/klee.h>

int sample(int a[4], int b[4], int target)
{
  int i, fa, fb;
  i=0;
  fa=0;
  fb=0;
  while(i<=3){
    if(a[i]==target) fa=1;
    ++i;
  };
  if(fa==1){
    i=0;
    fb=1;
    while(i<=3){
      if(b[i]!=target) fb=0;
      ++i;
    }
  }
  if(fb==1) return 0;
  else return 1;
}

int main(int argc, char **argv) {
  int a[4], b[4], target;

  klee_make_symbolic(a, 4 * sizeof(int), "a");
  klee_make_symbolic(b, 4 * sizeof(int), "b");
  klee_make_symbolic(&target, sizeof(int), "target");

  sample(a, b, target);
  return 0;
}
