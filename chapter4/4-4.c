#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>

#define MAXLINE 1000
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
double top(void);
void swap(void);
void clear(void);

int main(void) {
    push(1);
    push(2);
    printf("%g\n", top());
    swap();
    printf("%g\n", top());
    clear();
    printf("%g\n", top());
    return 0;
}


#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* top: get top value from stack */
double top(void) { 
    if (sp > 0)
        return val[sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* swap: swap the top two value in stack */
void swap(void) {
    if (sp >= 2) {
        double tmp = val[sp];
        val[sp] = val[sp-1];
        val[sp-1] = tmp;
    } else {
        printf("error: stack value less than 2, can't swap\n");
    }
}

/* clear: clear the stack */
void clear(void) {
    while (sp) pop();
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c, c2;

    while ((s[0] = c = getch()) == ' ' || c == '\t');
    s[1] = '\0';    
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */
    i = 0;
    if (c == '-') {
        c2 = getch();
        if (c2 != EOF)
            ungetch(c2);
        if (!isdigit(c2) && c2 != '.')
            return c;
    }
    if (isdigit(c) || c == '-') /* collect integer part */
        while (isdigit(s[++i] = c = getch()));
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()));
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int getch(void) {/* get a (possibly pushed-back) character */
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {/* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

