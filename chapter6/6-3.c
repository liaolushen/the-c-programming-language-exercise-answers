#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 1000

/* 行数记录节点 */
struct linenumber {
  int number;
  struct linenumber *next_linenumber;
};

/* 单词树节点 */
struct tnode {
    char *word;
    struct linenumber *linenumbers;
    struct tnode *left;
    struct tnode *right;
};

int getword(char *);
void treeprint(const struct tnode *);
struct tnode *addtree(struct tnode *, char *, int);
struct linenumber *addnumber(struct linenumber *, int);

struct tnode *talloc(void);
struct linenumber *lnalloc(int);
char *mstrdup(char *);
int getch(void);
void ungetch(int);

int main(int argc, char const *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int number;
    root = NULL;
    while ((number = getword(word)) && number > 0) {
        root = addtree(root, word, number);
    }
    treeprint(root);
    return 0;
}

int getword(char *word) {
    static int ln = 1;
    int c;
    char *w = word;

    while (c = getch()) {
        if (c == EOF) return -1;
        if (isalnum(c)) break;
        if (c == '\n') {
            ln++;
        }
    }

    while (c != EOF) {
        if (isalnum(c)) {
            *w++ = c;
        } else {
            ungetch(c);
            break;
        }
        *w = '\0';
        c = getch();
    }

    *w = '\0';
    return ln;
}

void treeprint(const struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s:\n", p->word);
        struct linenumber *ln = p->linenumbers;
        while (ln != NULL) {
            printf("%10d\n", ln->number);
            ln = ln->next_linenumber;
        }
        treeprint(p->right);
    }
}

struct tnode *addtree(struct tnode *p, char *w, int num) {
    if (p == NULL) {
        p = talloc();
        p->word = mstrdup(w);
        p->linenumbers = lnalloc(num);
        p->left = p->right = NULL;
    } else {
        int cond = strcmp(p->word, w);
        if (cond == 0) {
            addnumber(p->linenumbers, num);
        } else if (cond > 0) {
            p->left = addtree(p->left, w, num);
        } else {
            p->right = addtree(p->right, w, num);
        }
    }
    return p;
}

struct linenumber *addnumber(struct linenumber *ln, int num) {
    if (ln == NULL) {
        ln = lnalloc(num);
    }

    if (ln->number != num) {
        ln->next_linenumber = addnumber(ln->next_linenumber, num);
    }

    return ln;
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct linenumber *lnalloc(int num) {
    struct linenumber *ln = (struct linenumber *) malloc(sizeof(struct linenumber));
    ln->number = num;
    ln->next_linenumber = NULL;
}

char *mstrdup(char *s) {
    char *p;
    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL) strcpy(p, s);
    return p;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch() */
int bufp = 0;       /* next free position in buf */

int getch(void) { /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {  /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
    return;
}
