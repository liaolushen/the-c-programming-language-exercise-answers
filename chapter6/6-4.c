/*
 * 先以单纯构建一个树，完成全文的读取后，在以出现频率构建一棵新树
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 1000
#define BUFSIZE 100

/* 单词树节点 */
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int getword(char *);
void treeprint(const struct tnode *);
struct tnode *addtree_by_word(struct tnode *, char *);
struct tnode *addtree_by_count(struct tnode *, char *, int);
struct tnode *parse_new_tree(const struct tnode *old_root, struct tnode *new_root);

struct tnode *talloc(void);
char *mstrdup(char *);
int getch(void);
void ungetch(int);

int main(int argc, char const *argv[]) {
    struct tnode *root = NULL;
    char word[MAXWORD];
    int number;
    while (getword(word) != EOF) {
        root = addtree_by_word(root, word);
    }
    struct tnode *new_root = NULL;
    new_root = parse_new_tree(root, new_root);
    treeprint(new_root);
    return 0;
}

int getword(char *word) {
    int c;
    char *w = word;

    while ((c = getch()) != EOF) {
        if (isalnum(c)) break;
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

    return c;
}

void treeprint(const struct tnode *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n",p->count, p->word);
        treeprint(p->right);
    }
}

struct tnode *addtree_by_word(struct tnode *p, char *w) {
    if (p == NULL) {
        p = talloc();
        p->word = mstrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else {
        int cond = strcmp(p->word, w);
        if (cond == 0) {
            p->count++;
        } else if (cond > 0) {
            p->left = addtree_by_word(p->left, w);
        } else {
            p->right = addtree_by_word(p->right, w);
        }
    }
    return p;
}

struct tnode *addtree_by_count(struct tnode *p, char *w, int c) {
    if (p == NULL) {
        p = talloc();
        p->word = mstrdup(w);
        p->count = c;
        p->left = p->right = NULL;
    } else {
        if (strcmp(p->word, w) == 0) {
            p->count += c;
        } else if (p->count > c) {
            p->left = addtree_by_count(p->left, w, c);
        } else {
            p->right = addtree_by_count(p->right, w, c);
        }
    }
    return p;
}

struct tnode *parse_new_tree(const struct tnode *old_root, struct tnode *new_root) {
    if (old_root != NULL) {
        new_root = parse_new_tree(old_root->left, new_root);
        new_root = addtree_by_count(new_root, old_root->word, old_root->count);
        new_root = parse_new_tree(old_root->right, new_root);
    }
    return new_root;
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
