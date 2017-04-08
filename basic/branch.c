/*
 * From the discussion in
 * http://www.mail-archive.com/klee-dev@imperial.ac.uk/msg02327.html.
 *
 * KLEE displays a low coverage using klee-stats on small examples,
 * due to additional code added.  The additional code is displayed in
 * <klee_output_dir>/assembly.ll.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

int main() {
  int x;
  int y;
  int z;

#ifdef LLBMC
  x = __llbmc_nondef_int();
  y = __llbmc_nondef_int();
  z = __llbmc_nondef_int();
#else
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");
  klee_make_symbolic(&z, sizeof(z), "z");
#endif

  if (x < 1) {
    if (y < 0)
      y = 0;
  } else {
    y = 1;
  }

  return 0;
}
