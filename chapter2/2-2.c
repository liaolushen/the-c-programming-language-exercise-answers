#include <stdio.h>

#define LIMIT 1000

int main() {
    int i;
    int c, lim;
    char s[LIMIT];
    lim = LIMIT;

    for (i = 0; (i < lim-1) & ((c=getchar()) != '\n') & (c != EOF); ++i) {
        s[i] = c;
    }
    s[i] = '\0';
    printf("%s\n", s);
}

