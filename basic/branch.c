/*
 * From the discussion in
 * http://www.mail-archive.com/klee-dev@imperial.ac.uk/msg02327.html.
 *
 * KLEE displays a low coverage using klee-stats on small examples,
 * due to additional code added.  The additional code is displayed in
 * <klee_output_dir>/assembly.ll.
 */
#include <klee/klee.h>

int main() {
  int x;
  int y;
  int z;

  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");
  klee_make_symbolic(&z, sizeof(z), "z");

  if (x < 1) {
    if (y < 0)
      y = 0;
  } else {
    y = 1;
  }

  return 0;
}
