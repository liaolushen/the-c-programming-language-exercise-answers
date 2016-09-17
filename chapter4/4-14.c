#include <stdio.h>

#define swap(t, x, y) {t z; z = x; x = y; y = z;}

int main() {
    int a = 10, b = 11;
    swap(int, a, b);
    printf("a = %d, b = %d\n", a, b);
}
