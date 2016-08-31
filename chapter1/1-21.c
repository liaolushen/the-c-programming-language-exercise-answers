#include <stdio.h>

#define TABINC 8    // tab对应的空格数量

void put_blank(int blank_num);

int main() {
    int c;
    int pos; // 记录当前列的位置
    int blank_num; // 记录当前的空格数量
    pos = 0;
    blank_num = 0;
    while ((c = getchar()) != EOF) {
        ++pos;
        if (c == ' ') {
            if (pos % TABINC == 0) {
                putchar('\t');
                blank_num = 0;
            } else {
                ++blank_num;
            }
        } else if (c == '\t') {
            putchar('\t');
            pos += TABINC - pos % TABINC;
            blank_num = 0;
        } else if (c == '\n') {
            putchar(c);
            pos = 0;
            blank_num = 0;
        } else {
            put_blank(blank_num);
            putchar(c);
            blank_num = 0;
        }
    }
}

void put_blank(int blank_num) {
    for (int i = 0; i < blank_num; ++i) {
        putchar(' ');
    }
}

