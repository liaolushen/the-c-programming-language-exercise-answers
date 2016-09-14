// 在补码的表示中负数的范围是比正数要大1的，所以无法实现
#include <stdio.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main() {
    char s[100];
    itoa(100, s);
    printf("%s\n", s);
    itoa(-100, s);
    printf("%s\n", s);
}

void itoa(int n, char s[]) {
    int i, sign;
    i = 0;
    sign = n;
    do {
        s[i++] = sign < 0 ? (-(n % 10) + '0') : (n % 10 + '0');
    } while ((n /= 10) != 0);
    if (sign < 0) s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    int i, j;
    int tmp;

    for (j = 0; s[j] != '\0'; ++j);
    --j;

    for (i = 0; i < j; ++i, --j) {
        s[i] = s[i] ^ s[j];
        s[j] = s[i] ^ s[j];
        s[i] = s[i] ^ s[j];
    }
}

