#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>

#define MAXLINE 1000
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

int main(void) {
    int type;
    double a, op2;
    char s[MAXOP], buf[MAXOP];
    char e;

    while ((scanf("%s%c", s, &e)) == 2) {
        if (sscanf(s, "%lf", &a) == 1) {
            push(a);
        } else if (sscanf(s, "%s", buf)) {
                 for (char *c = buf ; *c; c++) {
                     switch (*c) {
                     case '+':
                         push(pop() + pop());
                         break;
                     case '-':
                         op2 = pop();
                         push(pop() - op2);
                         break;
                     case '*':
                         push(pop() * pop());
                         break;
                     case '/':
                         op2 = pop();
                         if (op2 != 0.0)
                             push(pop() / op2);
                         else
                             printf("error: zero divisor\n");
                         break;
                     default:
                         printf("Unknown command\n");
                         break;
                     }
                 } /* for */
                 if (e == '\n') /* print result */
                     printf("= %.8g\n", pop());
             }
    }

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
