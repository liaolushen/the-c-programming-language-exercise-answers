#include <stdio.h>

#define MAXLINE 1000
#define LINE_LIMIT 80

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > LINE_LIMIT) printf("%s", line);
    }

    return 0;    
}


int get_line(char line[], int maxline) {
    int c, i;
    for (i = 0; i < maxline-1 && (c=getchar()) != EOF && c!= '\n'; ++i) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

