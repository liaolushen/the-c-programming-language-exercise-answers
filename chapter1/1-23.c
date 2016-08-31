/*
 * Exercise 1-23. Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments don't nest.
 */

#include <stdio.h>


#define IN_SINGLE_QUOTES 1
#define IN_DOUBLE_QUOTES 2
#define IN_LINE_COMMENT 3
#define IN_BLOCK_COMMENT 4
#define OUT 0

int main() {
    int c, c_next, state;
    state = OUT;
    while ((c = getchar()) != EOF) {
        if (state == IN_SINGLE_QUOTES) {  // 当前处于单引号字符串中
            putchar(c);
            if (c == '\\') {
                putchar(getchar());
            } else if (c == '\'') {
                state = OUT;
            }
        } else if (state == IN_DOUBLE_QUOTES) {  // 当前处于双引号字符串中
            putchar(c);
            if (c == '\\') {
                putchar(getchar());
            } else if (c == '\"') {
                state = OUT;
            }
        } else if (state == IN_LINE_COMMENT) {  // 当前处于行注释中
            if (c == '\n') {
                putchar(c);
                state = OUT;
            }
        } else if (state == IN_BLOCK_COMMENT) {  // 当前处于块注释中
            if (c == '*') {
                c_next = getchar();
                if (c_next == '/') {
                    state = OUT;
                }
            }
        } else {  // 处于其他状态 
            if (c == '\'') {
                putchar(c);
                state = IN_SINGLE_QUOTES;
            } else if (c == '\"') {
                putchar(c);
                state = IN_DOUBLE_QUOTES;
            } else if (c == '/') {
                c_next = getchar();
                if (c_next == '*') {
                    state = IN_BLOCK_COMMENT;
                } else if (c_next == '/') {
                    state = IN_LINE_COMMENT;
                } else {
                    putchar(c);
                    putchar(c_next);
                }
            } else {
                putchar(c);
            }
        }
    }
}

