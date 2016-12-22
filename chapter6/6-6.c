#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100
#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch() */
int bufp = 0;       /* next free position in buf */

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *name, char *defn);
int undef(char *name);
int getword(char *word, int lim);
int getch(void);
void ungetch(int);

int main(int argc, char *argv[]) {
    char word[MAXWORD];
    char name[MAXWORD], defn[MAXWORD];
    while (getword(word, MAXWORD) != EOF) {
        if (strcmp(word, "#define") == 0) {
            getword(name, MAXWORD);
            getword(defn, MAXWORD);
            install(name, defn);
        }
    }
    struct nlist *p;
    for (int i = 0; i < HASHSIZE; i++) {
        p = hashtab[i];
        while (p != NULL) {
            printf("%s->%s\n", p->name, p->defn);
            p = p->next;
        }
    }
    return 0;
}


unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np=hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) return np;
    }
    return NULL;
}


struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL) return NULL;
    return np;
}


int undef(char *name) {
    struct nlist *np, *np_before;
    unsigned hashval;

    if ((np = lookup(name)) != NULL) {
        hashval = hash(name);
        np_before = hashtab[hashval];
        while (np_before->next != NULL) {
            if (strcmp(np_before->next->name, name) == 0) break;
            np_before = np_before->next;
        }

        if (np_before->next == NULL) {
            hashtab[hashval] = NULL;
        } else {
            np_before->next = np->next;
        }
        free((void *) np->name);
        free(np->defn);
        free(np);

        return 0;
    }
    return 1;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()));

    if (c != EOF) *w++ = c;


    for (; --lim > 0; w++) {
        if (isspace(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

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
