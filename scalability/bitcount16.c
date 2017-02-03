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
#include <string.h>
#include <stdint.h>

uint16_t nBC1(uint16_t nX)
{
  uint16_t res = 0;
  size_t nI;
  for (nI = 0; nI < 8*sizeof(uint16_t); nI++) {
    res += (nX & (1 << nI)) ? 1 : 0;
  }
  return res;
}

uint16_t nBC2(uint16_t nX)
{
  uint16_t res = nX;
  res = (res & 0x5555) + (res >> 1  & 0x5555);
  res = (res & 0x3333) + (res >> 2  & 0x3333);
  res = (res & 0x0F0F) + (res >> 4  & 0x0F0F);
  res = (res & 0x00FF) + (res >> 8  & 0x00FF);
  return res;
}

#ifdef LLBMC
void __llbmc_main(int nX) { __llbmc_assert(nBC1(nX) == nBC2(nX)); }
#else
int main(int nX)
{
  int nX;
  klee_make_symbolic(&nX, sizeof(nX), "nX");
  assert(nBC1(nX) == nBC2(nX));
  return 0;
}
#endif
