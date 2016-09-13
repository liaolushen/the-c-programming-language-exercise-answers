#include <stdio.h>

unsigned reverse(unsigned x, int p, int n);

int main() {
    printf("%u == 10\n", reverse(12, 2, 2));
    printf("%u == 8\n", reverse(12, 2, 1));
    printf("%u == 15\n", reverse(12, 1, 2));
}

unsigned reverse(unsigned x, int p, int n) {
    unsigned code = ~(~0 << n) << (p+1-n);
    return (x & ~code) + (~(x & code) & code);
}
