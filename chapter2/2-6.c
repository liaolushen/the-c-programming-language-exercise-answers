#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main() {
    printf("%u == 15\n", setbits(12, 1, 2, 3));
    printf("%u == 14\n", setbits(12, 1, 1, 3));
    printf("%u == 13\n", setbits(12, 1, 2, 1));
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned a = (y & ~(~0 << n)) << (p+1-n);
    unsigned b = x - (x & (~(~0 << n) << (p+1-n)));
    return a + b;
}
