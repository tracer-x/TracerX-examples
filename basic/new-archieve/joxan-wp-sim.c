#include <klee/klee.h>

int sum = 0;
int a[5] = {1, 10, 100, 1000, -1};

int main() {
    int c;
    c = choice(a);
    if (c == -1) exit(0);
    sum += c;
    klee_assert(sum <= 9000);
}

int choice(int *a) {
    int c;
    klee_make_symbolic(&c, sizeof(unsigned), "c");
    if (*a == -1) return -1;
    if (c) return choice(a + 1); else { return a[0]; }
}
