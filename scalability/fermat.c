/*
 * Example from urbina directory of
 * http://llbmc.org/files/downloads/llbmc-bench-1.1.tgz with KLEE
 * harness added.
 */
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include <stdlib.h>

uint32_t nPow(uint32_t nx, int np) {
  uint32_t nPow = 1;
  int ni;
  for (ni = 0; ni < np; ni++) {
    nPow *= nx;
  }
  return nPow;
}

#ifdef LLBMC
void __llbmc_main(uint32_t na, uint32_t nb, uint32_t nc) {
#else
  void main() {
    uint32_t na;
    uint32_t nb;
    uint32_t nc;
    klee_make_symbolic(&na, sizeof(na), "na");
    klee_make_symbolic(&nb, sizeof(nb), "nb");
    klee_make_symbolic(&nc, sizeof(nc), "nc");
#endif

    int nN = 3;
#ifdef LLBMC
    __llbmc_assume(na > 0);
    __llbmc_assume(nb > 0);
    __llbmc_assume(nc > 0);
    __llbmc_assert(nPow(na, nN) + nPow(nb, nN) != nPow(nc, nN));
#else
    klee_assume(na > 0);
    klee_assume(nb > 0);
    klee_assume(nc > 0);
    klee_assert(nPow(na, nN) + nPow(nb, nN) != nPow(nc, nN));
#endif
  }
