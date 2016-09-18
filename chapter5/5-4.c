#include <stdio.h>

#define MAXSIZE 1000

void str_cat(char *s, char *t);
int strend(char *s, char *t);

int main() {
    char s[MAXSIZE] = "hello";
    char t[MAXSIZE] = "world";

    printf("%d\n", strend(s, t));
    str_cat(s, t);
    printf("%d\n", strend(s, t));
}

void str_cat(char *s, char *t) {
    for (; *s != '\0'; s++);
    while (*s++ = *t++);
}

int strend(char *s, char *t) {
    char *s_x, *t_x;
    for (s_x = s; *s_x != '\0'; s_x++);
    for (t_x = t; *t_x != '\0'; t_x++);

    while ((*t_x-- == *s_x--) && (t_x > t) && (s_x > s));

    if (t_x == t) return 1;
    return 0;
}
