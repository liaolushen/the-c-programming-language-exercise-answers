#include <stdio.h>

#define LINE_WIDTH 10
#define TABINC 8

void put_blank(int blank_num);

int main() {
    int c;
    int pos, blank_num;
    pos = 0;
    blank_num = 0;
    while ((c = getchar()) != EOF) {
        ++pos;
        if (c == '\n') {
            pos = 0;
            putchar(c);
        } else if (c == ' ') {
            ++blank_num;
            if (pos >= LINE_WIDTH) {
                putchar('\n');
                pos = blank_num;
            }
        } else {
            put_blank(blank_num);
            blank_num = 0;
            if (c == '\t') {
                pos += TABINC - pos % TABINC;
            }
            putchar(c);

            if (pos >= LINE_WIDTH) {
                putchar('\n');
                pos = 0;
            }
        }
    }
}


void put_blank(int blank_num) {
    for (int i = 0; i < blank_num; ++i) {
        putchar(' ');
    }
}

