#include <stdio.h>
#include <klee/klee.h>
int main() {
    int x = 0;
    int y = 0;
    int a[1], b[5];
    klee_make_symbolic(b,sizeof(int)*5,"b");
    int i = 0;
    while(i < 5) {
       if (b[i] > 0) 
       x = x + (i+2)*5; 
       else x = x + 0;
       if (i == 4 && b[1] > 0) 
       x = x + 0; 
       else x = x + 30;	
       i++;
    }
    int BOUND = 130;
    if (BOUND == x) {y++;}
    a[y] = 5;
    return 0;
}
