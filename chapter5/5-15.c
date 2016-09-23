#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void mqsort(void *lineptr[], int nlines, int right,
        int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int flod_strcmp(const char *, const char *);
void reverse(char *lineptr[], int nlines);


int main(int argc, char *argv[]) {
    int nlines;
    int is_numeric = 0;
    int is_reverse = 0;
    int is_flod = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) is_numeric = 1;
        if (strcmp(argv[i], "-r") == 0) is_reverse = 1;
        if (strcmp(argv[i], "-f") == 0) is_flod = 1;

    }


    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (is_numeric) {
            mqsort((void **) lineptr, 0, nlines-1,
                (int (*)(void*, void*))(numcmp));
        } else if (is_flod) {
            mqsort((void **) lineptr, 0, nlines-1,
                (int (*)(void*, void*))(flod_strcmp));
        } else {
            mqsort((void **) lineptr, 0, nlines-1,
                (int (*)(void*, void*))(strcmp));
        }
        if (is_reverse) reverse(lineptr, nlines);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000

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


int flod_strcmp(const char *s1, const char *s2) {
    for (; tolower(*s1) == tolower(*s2); s1++, s2++) {
        if (*s1 == '\0') return 0;
    }
    return tolower(*s1) - tolower(*s2);
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

