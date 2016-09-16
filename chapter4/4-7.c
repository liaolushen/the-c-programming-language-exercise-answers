#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void);
void ungetch(int c);
void ungets(char s[]);

int main() {
    ungets("hello");
    printf("%c\n", getch());
    printf("%c\n", getch());
    printf("%c\n", getch());
    printf("%c\n", getch());
    printf("%c\n", getch());
}

int getch(void) {/* get a (possibly pushed-back) character */
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {/* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) ungetch(s[i]);
}

