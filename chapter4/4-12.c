#include <stdio.h>
#include <stdlib.h>


void itoa(char s[], int n);

int main() {
    char s[100];
    itoa(s, -100);
    printf("%s\n", s);
    itoa(s, 123);
    printf("%s\n", s);
    itoa(s, 0);
    printf("%s\n", s);
}


void itoa(char s[], int n) {
    static int i;

    if (n/10) {
        itoa(s, n/10);
    } else {
        i = 0;
        if (n < 0) {
            s[i++] = '-';
        }
    }
    s[i++] = abs(n) % 10 + '0';
    s[i] = '\0';
}

