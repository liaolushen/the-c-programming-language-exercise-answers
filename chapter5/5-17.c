/* Usage: sort -dfnr [+pos_begin] [-pos2] */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLEN 1000

#define NUMERIC 1
#define DECR    2
#define FOLD    4
#define MDIR    8


char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void mqsort(void *lineptr[], int nlines, int right,
        int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int charcmp(const char *, const char *);
void reverse(char *lineptr[], int nlines);
void error(char *);

int option = 0;
int pos1 = 0;
int pos2 = 0;


int main(int argc, char *argv[]) {
    int nlines;
    int c;

    while (--argc > 0 && (c=(*++argv)[0]) == '-' || c == '+') {
        if (c == '-' && !isdigit(*(argv[0]+1))) {
            while (c = *++argv[0]) {
                switch(c) {
                    case 'd':
                        option |= MDIR;
                        break;
                    case 'f':
                        option |= FOLD;
                        break;
                    case 'n':
                        option |= NUMERIC;
                        break;
                    case 'r':
                        option |= DECR;
                        break;
                    default:
                        printf("sort: illegal option %c\n", c);
                        argc = 1;
                        break;
                }
            }
        } else if (c == '-') {
            pos2 = atoi(argv[0]+1);
        } else if (c == '+') {
            pos1 = atoi(argv[0]+1);
            if (pos1 < 0) error("Usage: sort -dfnr [+pos1][-pos2]");
        }

    }

    if (argc || pos1 > pos2) {
        error("Usage: sort -dfnr [+pos1][-pos2]");
    } else {      
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
            if (option & NUMERIC) {
                mqsort((void **) lineptr, 0, nlines-1,
                    (int (*)(void*, void*))(numcmp));
            } else {
                mqsort((void **) lineptr, 0, nlines-1,
                    (int (*)(void*, void*))(charcmp));
            }
            if (option & DECR) reverse(lineptr, nlines);
            writelines(lineptr, nlines);
            return 0;
        } else {
            printf("input too big to sort\n");
            return 1;
        }
    }
}

void error(char *s) {
    printf("%s \n",s);
    exit(1);
}


int get_line(char *line, int maxline);
char *alloc(int);
void swap (void *v[], int i, int j);

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
            return -1;
        } else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) printf("%s\n", lineptr[i]);
}

void mqsort(void *v[], int left, int right,
        int (*comp)(void *, void *)) {
    int i, last;
    if (left >= right) return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) swap(v, ++last, i);
    }
    swap(v, left, last);
    mqsort(v, left, last-1, comp);
    mqsort(v, last+1, right, comp);
}


int numcmp(const char *s1, const char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    else return 0;
}


int charcmp(const char *s, const char *t) {
    char a, b;
    int i, j, endpos;
    int fold = (option & FOLD) ? 1 : 0;
    int dir = (option & MDIR) ? 1 : 0;


    i = j = pos1;
    if (pos2 > 0) endpos = pos2;
    else if ((endpos = strlen(s)) > strlen(t)) endpos = strlen(t);

    do {
        if (dir) {
            while (i < endpos && isalnum(s[i]) && s[i] != ' ' && s[i] != '\0')
                i++;
            while (j < endpos && isalnum(t[j]) && t[j] != ' ' && t[j] != '\0')
                j++;
        }

        if (i < endpos && j < endpos) {
            a = fold ? tolower(s[i]) : s[i];
            i++;
            b = fold ? tolower(t[j]) : t[j];
            j++;

            if (a == b && a == '\0') return 0;
        }
    } while (a == b && i < endpos && j < endpos);
    return a - b;
}


void reverse(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines/2; i++) swap((void **)lineptr, i, nlines-i-1);
}

void swap(void *v[], int i, int j) {
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int get_line(char *line, int maxline) {
    int c, i;
    for (i = 0; i < maxline-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
        *line++ = c;
    }
    if (c == '\n') {
        *line++ = c;
        ++i;
    }
    *line = '\0';
    return i;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp -n;
    } else {
        return 0;
    }
}

