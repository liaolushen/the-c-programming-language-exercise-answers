#include <stdio.h>

#define CHAR_LEN 26

int main() {
    int c;
    int nchar[CHAR_LEN];
    for (int i = 0; i < CHAR_LEN; i++) {
        nchar[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c >= 'a' && c <= 'z') {
            nchar[c - 'a']++;
        }
    }

    for (int i = 0; i < CHAR_LEN; i++) {
        printf("%c:", i+'a');
        for (int j = 0; j < nchar[i]; j++) {
            putchar('|');
        }
        putchar('\n');
    }
}

