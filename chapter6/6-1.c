#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 1000


int getword(char *word, int lim);
int getch(void);
void ungetch(int c);
void getstring(char *word, int lim);


int main() {
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF) {
        printf("%s\n", word);
    }
}



int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()));

    if (c != EOF) *w++ = c;

    if (c == '\"' || c == '\'') {
        getstring(w, lim);
        return word[0];
    }

    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch()) && (*w) != '_') {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

void getstring(char *word, int lim) {
    int c;
    for (; --lim > 0; word++) {
        c = getch();
        if (c == '\\') {
            *word++ = c;
            *word = getch();
            --lim;
        } else if (c == '\'' || c == '\"') {
            *word = c;
            break;
        } else {
            *word = c;
        }
    }
    *++word = '\0';
}


char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many charaters\n");
    else
        buf[bufp++] = c;
}

