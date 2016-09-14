#include <stdio.h>

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main() {
    char s[100];
    itoa(100, s, 20);
    printf("%s\n", s);
    itoa(-100, s, 5);
    printf("%s\n", s);
}

void itoa(int n, char s[], int w) {
    int i, sign;
    i = 0;
    sign = n;
    do {
        s[i++] = sign < 0 ? (-(n % 10) + '0') : (n % 10 + '0');
    } while ((n /= 10) != 0);
    if (sign < 0) s[i++] = '-';
    while (i < w) s[i++] = ' ';
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

