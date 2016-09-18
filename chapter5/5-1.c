#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

int buf[BUFSIZE]; /* char类型改为int类型即可 */
int bufp = 0; /* next free position in buf */

int getch(void);
void ungetch(int c);
int getint(int *pn);

int main() {
    for (int i = 0; i < 5; i++) {
        int a;
        getint(&a);
        printf("%d\n", a);
    }
}

int getint(int *pn) {
    int c, sign;
    *pn = 0;
    while (isspace(c = getch()));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) *pn = 0;
    }

    while (isdigit(c)) {
        *pn = 10 * (*pn) + (c - '0');
        c = getch();
    }

    *pn *= sign;
    if (c != EOF) ungetch(c);
    return c;
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

