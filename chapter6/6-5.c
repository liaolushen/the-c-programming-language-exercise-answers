#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASHSIZE 101

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

int main(int argc, char *argv[]) {
    struct nlist *table[4] = {
            (install("key", "value")),
            (install("key1", "value1")),
            (install("key2", "value2")),
            (install("key3", "value3"))
    };

    int i;

    for (i=0; i < 4; i++) {
        printf("%s->%s\n", table[i]->name, table[i]->defn);
    }

    undef("key");
    undef("key3");

    struct nlist *result;

    char *keys[4] = {
            "key",
            "key1",
            "key2",
            "key3"
    };

    for (i = 0; i < 4; i++) {
        if ((result = lookup(keys[i])) == NULL) {
            printf("key not found\n");
        } else {
            printf("%s->%s\n", result->name, result->defn);
        }
    }

    return 0;
}
