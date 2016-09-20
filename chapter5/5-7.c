#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];
char linestor[MAXLINES];

int readlines(char *lineptr[], char* linestor, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);


int main() {
    int nlines;

    if ((nlines = readlines(lineptr, linestor, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}


#define MAXLEN 1000
#define MAXSTOR 10000

int get_line(char *line, int maxline);
char *alloc(int);

int readlines(char *lineptr[], char *linestor, int maxlines) {
    int len, nlines;
    char line[MAXLEN];
    char *p = linestor;
    char *linestop = linestor + MAXSTOR;

    nlines = 0;

    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || p+len > linestop) {
            return -1;
        } else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    for (int i = 0; i < nlines; i++) printf("%s\n", lineptr[i]);
}

void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);
    if (left >= right) return;
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) swap(v, ++last, i);
        swap(v, left, last);
        qsort(v, left, last-1);
        qsort(v, last+1, right);
    }
}

void swap(char *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int get_line(char *line, int maxline) {
    int c, i;
    for (i = 0; i < maxline-1 && (c=getchar()) != EOF && c!= '\n'; ++i) *line++ = c;
    if (c == '\n') {
        *line++ = c;
        ++i;
    }
    line = '\0';
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
