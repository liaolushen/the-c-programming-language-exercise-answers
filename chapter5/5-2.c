#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

int buf[BUFSIZE]; /* char类型改为int类型即可 */
int bufp = 0; /* next free position in buf */

int getch(void);
void ungetch(int c);
int getfloat(double *pn);

int main() {
    for (int i = 0; i < 5; i++) {
        double a;
        getfloat(&a);
        printf("%g\n", a);
    }
}

int getfloat(double *pn) {
    int c, sign;
    double power;
    *pn = 0.0;
    power = 1.0;
    while (isspace(c = getch()));

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') *pn = 0;
    }

    while (isdigit(c)) {
        *pn = 10 * (*pn) + (c - '0');
        c = getch();
    }

    if (c == '.') {
        c = getch();
        while (isdigit(c)) {
            *pn = 10 * (*pn) + (c - '0');
            power *= 10;
            c = getch();
        }
    }


    *pn *= sign / power;
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

