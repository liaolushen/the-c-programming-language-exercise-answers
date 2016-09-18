#include <stdio.h>

#define MAXSIZE 1000

int get_line(char *s, int lim);
int atoi(char *s);
void itoa(int n, char *s);
void reverse(char *s);


int main() {
    char s[MAXSIZE];
    get_line(s, MAXSIZE);
    printf("%s\n", s);
    int a = atoi(s);
    printf("%d\n", a);
    itoa(a, s);
    printf("%s\n", s);
}

int get_line(char *s, int lim) {
    int n;
    for (n = 1; *s = getchar(); n++, s++) {
        if (n == lim - 1 || *s == '\n') break;
    }

    *s = '\0';
    return n;
}


int atoi(char *s) {
    int i, n, sign;
    n = 0;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '-' || *s == '+') s++;
    for (; *s != '\0'; s++) {
        n = 10 * n + (*s - '0');
    }
    return n * sign;
}


void itoa(int n, char *s) {
    int sign;
    char *s_x;
    s_x = s;
    if ((sign = n) < 0) n = -n;
    do {
        *s_x++ = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) *s_x++ = '-';
    *s_x = '\0';
    reverse(s);
}

void reverse(char *s) {
    char *s_x;
    s_x = s;
    while (*s_x) s_x++;
    s_x--;
    while (s_x > s) {
        *s_x ^= *s;
        *s ^= *s_x;
        *s_x ^= *s;
        s++;
        s_x--;
    }
}

