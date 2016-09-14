#include <stdio.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
    char s[100];
    itob(13, s, 16);
    printf("%s\n", s);
    itob(-100, s, 2);
    printf("%s\n", s);
}

void itob(int n, char s[], int b) {
    int i, sign, d;
    i = 0;
    sign = n;
    do {
        d = sign < 0 ? -(n % b) : (n % b);
        if (d >= 10) s[i++] = d - 10 + 'a';
        else s[i++] = d + '0';
    } while ((n /= b) != 0);
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

