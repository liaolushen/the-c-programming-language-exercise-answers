#include <stdio.h>

#define MAXSIZE 1000

void str_cat(char *s, char *t);

int main() {
    char s[MAXSIZE] = "hello";
    char t[MAXSIZE] = "world";

    str_cat(s, t);
    printf("%s\n", s);
}

void str_cat(char *s, char *t) {
    for (; *s != '\0'; s++);
    while (*s++ = *t++);
}
