#include <stdio.h>

int main() {
    int c1, c2;
    c1 = EOF;
    while ((c2 = getchar()) != EOF) {
        if (c2 != ' ' || c2 != c1) {
            c1 = c2;
            putchar(c1);
        }
    }
}

