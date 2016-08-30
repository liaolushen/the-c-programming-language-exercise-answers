#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
    int len, max, tmp_len;
    char line[MAXLINE], longest[MAXLINE], tmp_line[MAXLINE];

    max = 0;
    while ((len = get_line(line, MAXLINE)) > 0) {
        copy(tmp_line, line);
        tmp_len = len;
        while (tmp_line[tmp_len-1] != '\n') {
            tmp_len = get_line(tmp_line, MAXLINE);
            len += tmp_len;
        }

        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    if (max > 0) {
        printf("%3d:%s", max, longest);
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

