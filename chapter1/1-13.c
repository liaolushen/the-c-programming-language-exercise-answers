#include <stdio.h>

#define IN 1
#define OUT 2
#define MAX_LEN 20

int main() {
    int c, state, len;
    int word_len[MAX_LEN];
    state = OUT;
    len = 0;
    for (int i = 0; i < MAX_LEN; i++) {
        word_len[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                state = OUT;
                word_len[len]++;
                len = 0;
            }
        } else {
            state = IN;
            len++;
        }
    }

    for (int i = 1; i < MAX_LEN; i++) {
        printf("%2d:", i);
        for (int j = 0; j < word_len[i]; j++) {
            putchar('|');
        }
        putchar('\n');
    }
}

