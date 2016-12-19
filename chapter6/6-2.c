#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#define MAXWORD 1000
#define DEFAULT_COMP_LEN 6

/* 树的节点 */
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* 单词组 */
struct simroot {
    struct simword *firstword;
    struct simroot *nextroot;
};

/* 单词节点 */
struct simword {
    char *word;
    int count;
    struct simword *nextword;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(const struct tnode *);
int mgetword(char *, int);
struct simroot *addroot(struct simroot *, struct tnode *, int);
struct simroot *parse(struct tnode *, int);
void printlist(struct simroot *, int);
void printwords(struct simword *);


int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    struct simroot *listroot;
    int len;

    root = NULL;
    while (mgetword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) root = addtree(root, word);
    }


    // treeprint(root);

    if (argc == 1) {
        len = DEFAULT_COMP_LEN;
    } else if (argc == 2) {
        len = atoi(argv[1]);
    } else {
        printf("Incorrect number of arguments.\n");
        return 1;
    }

    listroot = NULL;
    listroot = parse(root, len);
    printf("\nDuplicate list:\n\n");
    printlist(listroot, len);

    return 0;
}

struct simroot *parse(struct tnode *node, int len) {
    struct tnode *temp;
    static struct simroot *root = NULL;

    if (node == NULL) return NULL;


    parse(node->left, len);

    root = addroot(root, node, len);

    parse(node->right, len);

    return root;
}


void printlist(struct simroot *p, int len) {
    int i;
    if (p == NULL)
        return;
    for (i = 0; i < len; ++i) {
        putchar(p->firstword->word[i]);
    }

    putchar('\n');
    printwords(p->firstword);
    putchar('\n');
    printlist(p->nextroot, len);
}

void printwords(struct simword *p) {
    printf(" %4d %s\n", p->count, p->word);
    if (p->nextword != NULL) {
        printwords(p->nextword);
    }
}

struct tnode *talloc(void);
char *mstrdup(char *);
struct simword *walloc(struct simword *, struct tnode *);
void addword(struct simword *, struct tnode *);

struct simroot *addroot(struct simroot *p, struct tnode *n, int len) {
    if (p == NULL) {
        p = (struct simroot *) malloc(sizeof(struct simroot));
        p->nextroot = NULL;
        p->firstword = walloc(p->firstword, n);
    } else if (strncmp(p->firstword->word, n->word, len) == 0) {
        addword(p->firstword, n);
    } else {
        p->nextroot = addroot(p->nextroot, n, len);
    }
    return p;
}

void addword(struct simword *p, struct tnode *n) {
    if (strcmp(p->word, n->word) == 0) return;

    if (p->nextword == NULL) {
        p->nextword = walloc(p->nextword, n);
    } else {
        addword(p->nextword, n);
    }
}

struct simword *walloc(struct simword *p, struct tnode *n) {
    p = (struct simword *) malloc(sizeof(struct simword));
    if (p != NULL) {
        p->word = n->word;
        p->count = n->count;
        p->nextword = NULL;
    }
    return p;
}

#define IN 1
#define OUT 0

int mgetword(char *word, int lim) {
    int c, getch(void);
    int line_comment, block_comment, string, directive, ascii;
    void ungetch(int);
    char *w = word;

    line_comment = block_comment = string = directive = ascii = OUT;

    while (isspace(c = getch()));

    if (c == '/') {
        int d;
        if ((d = getch()) == '*') {
            block_comment = IN;
        } else if (d == '/') {
            line_comment = IN;
        }
        ungetch(d);
    } else if (c == '\"') {
        string = IN;
    } else if (c == '#') {
        directive = IN;
    } else if (c == '\'') {
        ascii = IN;
    }

    if (block_comment == IN) {
        *w++ = c;
        *w++ = getch();

        while ((*w++ = c = getch())) {
            if (c == '*') {
                if ((c = getch()) == '/') {
                    *w++ = c;
                    block_comment = OUT;
                    break;
                } else {
                    ungetch(c);
                }
            }
        }
        *w = '\0';
    } else if (line_comment == IN) {
        *w++ = c;
        *w++ = getch();

        while ((*w++ = c = getch())) {
            if (c == '\n') {
                  block_comment = OUT;
                  break;
            }
        }
        *w = '\0';
    } else if (directive == IN) {
        *w++ = c;
        while ((*w++ = c = getch()) != '\n') {
            if (c == '\\') {
                *w++ = getch();
            }
        }
        directive = OUT;
        *w = '\0';
    } else if (string == IN) {
        *w++ = c;
        while ((*w++ = c = getch()) != '\"') {
            if (c == '\\') *w++ = getch();
        }
        string = OUT;
        *w = '\0';
    } else if (ascii == IN) {
      *w++ = c;
      while ((*w++ = c = getch()) != '\'') {
          if (c == '\\') *w++ = getch();
      }
      ascii = OUT;
      *w = '\0';
    } else {
        if (c != EOF) *w++ = c;

        if (!isalnum(c) && c != '_') {
            *w = '\0';
            return c;
        }

        for (; --lim > 0; w++) {
            *w = getch();
            if (!isalnum(*w) && *w != '_') {
                ungetch(*w);
                break;
            }
        }
        *w = '\0';
        return word[0];
    }

    return c;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = mstrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

void treeprint(const struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}


struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
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
