#include <klee/klee.h>
#define loop for(;;)

int count = 2, sum = 0;
int a[5] = {1, 10, 100, 1000, -1};

int main() {
    while (count--) {
        int c;
        c = choice(a);
        if (c == -1) exit(0);
        sum += c;
        printf("Choice %d Sum %d\n", c, sum);
    }
    printf("Final Sum %d\n", sum);
    klee_assert(sum <= 9000);

}

int choice(int *a) {
    int c;
    printf("choice(): a[0] = %d\n", a[0]);
    klee_make_symbolic(&c, sizeof(unsigned), "c");
    if (*a == -1) return -1;
    if (c) return choice(a + 1); else { printf("Return %d\n", a[0]); return a[0]; }
    // if (c) { printf("Return %d\n", a[0]); return a[0]; } else return choice(a + 1); 
}
