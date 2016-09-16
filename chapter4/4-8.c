#include <stdio.h>
#define BUFSIZE 100

int bufp = -1; /* 被压回的值 */

int getch(void);
void ungetch(int c);

int main() {
    ungetch('a');
    ungetch('b');
    printf("%c\n", getch());
}

int getch(void) {/* get a (possibly pushed-back) character */
        return (bufp > 0) ? bufp : getchar();
}

void ungetch(int c) {/* push character back on input */
    if (bufp > 0)
        printf("ungetch: too many characters\n");
    else
        bufp = c;
}


