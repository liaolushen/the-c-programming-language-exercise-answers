#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main() {
    printf("%u\n", rightrot(12, 1));
    printf("%u\n", rightrot(12, 3));
}

unsigned rightrot(unsigned x, int n) {
    while (n--) {
        if (x & 1) {
            x = (x >> 1) | (~(~0U >> 1)); // 需要显示声明0为unsigned类型
        } else {
            x = x >> 1;
        }
    }
    return x;
}
