#include <stdio.h>


int bitcount(unsigned x);

int main() {
    printf("12->%d\n", bitcount(12));
    printf("15->%d\n", bitcount(15));
}


int bitcount(unsigned x) {
    int b = 0;
    while (x) {
        x &= x - 1;
        b++;
    }
    return b;
}
