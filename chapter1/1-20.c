#include <stdio.h>

#define TABINC 8    // tab对应的空格数量

void put_blank(int blank_num);

int main() {
    int c;
    int pos; // 记录当前列的位置
    pos = 1;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int blank_num = TABINC - (pos-1) % TABINC;
            put_blank(blank_num);
            pos += blank_num;
        } else if (c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
    }
}

void put_blank(int blank_num) {
    for (int i = 0; i < blank_num; ++i) {
        putchar(' ');
    }
}

