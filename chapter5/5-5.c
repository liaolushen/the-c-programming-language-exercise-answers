#include <stdio.h>

#define MAXSIZE 1000

void str_ncpy(char *s, const char *t, int n);
void str_ncat(char *s, const char *t, int n);
int str_ncmp(const char *s, const char *t, int n);

int main() {
    char s[MAXSIZE];
    char t[MAXSIZE] = "size";

    str_ncpy(s, t, 2);
    printf("%s\n", s);

    str_ncat(s, t, 3);
    printf("%s\n", s);

    printf("%d\n", str_ncmp(s, "siz", 2));
}

void str_ncpy(char *s, const char *t, int n) {
    while (n-- && (*s++ = *t++));
}

void str_ncat(char *s, const char *t, int n) {
    while (*s) s++;
    str_ncpy(s, t, n);
}

int str_ncmp(const char *s, const char *t, int n) {
    for (;(*s == *t); s++, t++) {
        if (*s == '\0') return 0;
        if (--n == 0) break;
    }

    return *s - *t;
}
