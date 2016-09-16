#include <stdio.h>
#define BUFSIZE 100

int buf[BUFSIZE]; /* char类型改为int类型即可 */
int bufp = 0; /* next free position in buf */

int getch(void);
void ungetch(int c);

int main() {
    ungetch('1');
    ungetch(EOF);
    putchar(getch());
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

