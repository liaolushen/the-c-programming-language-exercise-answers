#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>

#define NUMBER '0' /* signal that a number was found */

int gettype(char *);
void push(double);
double pop(void);

int main(int argc, char *argv[]) {
    int op2;
    if (argc <= 1) {
        printf("Usage: expr xxxx\n");
        return 0;
    }


    int type;

    for (int i = 1; i < argc; i++) {
        type = gettype(argv[i]);
        printf("%s\n", argv[i]);
        switch (type) {
            case NUMBER:
                push(atof(argv[i]));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            default:
                printf("error: unknown command %s]\n", argv[i]);
                break;
        }
    }

    printf("%g\n", pop());
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

#include <ctype.h>

int gettype(char *s) {
    if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/') return s[0];
    return NUMBER;
}
