#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include <string.h>

#define MAXLINE 1000
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MATHLIB '1' /* 库操作符号 */
#define VARIABLE '2' /* 变量 */

int getop(char []);
void push(double);
double pop(void);

int main(void) {
    int type;
    double op2;
    double last_result = 0.0;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case MATHLIB:
                if (strcmp(s, "sin") == 0) {
                    push(sin(pop()));
                } else if (strcmp(s, "cos") == 0) {
                    push(cos(pop()));
                } else if (strcmp(s, "pow") == 0) {
                    op2 = pop();
                    push(pow(pop(), op2));
                } else {
                    printf("error: unknown command %s\n", s);
                }
                break;
            case VARIABLE:
                if (strcmp(s, "$") == 0) {
                    push(last_result);
                } else {
                    printf("error: unknown command %s\n", s);
                }
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
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                last_result = pop();
                printf("= %g\n", last_result);
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
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

#include <ctype.h>

#define MAXLINE 1000
int get_line(char s[], int lim);

int li = 0;
char line[MAXLINE];

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;

    if (line[li] == '\0') {
        if (get_line(line, MAXLINE) == 0) return EOF;
        else li = 0;
    }

    while ((s[0] = c = line[li++]) == ' ' || c == '\t');
    s[1] = '\0';
    i = 0;

    if (c == '$') { /* 上次计算的结果 */
        return VARIABLE;
    }

    if (islower(c)) { /* 库操作 */
        while (islower(s[++i] = c = line[li++]));
        li--;
        s[i] = '\0';
        return MATHLIB;
    }

    if (c == '-') { /* 减号操作符 */
        if (!isdigit(line[li]) && line[li] != '.') return c;
    }

    if (isdigit(c) || c == '-') { /* 数字 */
        while (isdigit(s[++i] = c = line[li++]));
        if (c == '.') {
            while (isdigit(s[++i] = c = line[li++]));
        }
        li--;
        s[i] = '\0';
        return NUMBER;
    }

    return c;
}

int get_line(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';                
    return i;
}

