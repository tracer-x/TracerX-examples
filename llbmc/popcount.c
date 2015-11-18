#include <stdint.h>
#include <assert.h>
#include <klee/klee.h>

uint32_t optimized_popcount(uint32_t x)
{
    x = x - ((x >> 1 ) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x += (x >> 8);
    x += (x >> 16);
    return x & 0x0000003F;
}

uint32_t reference_popcount(uint32_t x)
{
    int i, s = 0;
    for(i = 0; i < 32; ++i)
        if(x & (1 << i))
            s++;
    return s;
}

void __llbmc_main(uint32_t x)
{
    // The value of x is chosen non-deterministically by LLBMC.
    // The assertion below thus has to hold for all possible 
    // values of x.

    uint32_t opt = optimized_popcount(x);
    uint32_t ref = reference_popcount(x);

    // Show that both implementations of popcount produce the
    // same result for all values of x.

    assert(opt == ref);
}

int main() {
  uint32_t x;

  klee_make_symbolic(&x, sizeof(x), "x");

  __llbmc_main(x);

  return 0;
}
