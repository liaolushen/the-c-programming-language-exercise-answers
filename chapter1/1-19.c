#include <stdio.h>

#define MAXLINE 1000
#define LINE_LIMIT 80

int get_line(char line[], int maxline);
void reverse(char line[]);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
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


void reverse(char line[]) {
    int begin, end;
    begin = 0;
    for (end = 0; line[end] != '\0'; end++);
    end--;
    if (line[end] = '\n') end--;
    while (begin < end) {
        line[begin] ^= line[end];
        line[end] ^= line[begin];
        line[begin] ^= line[end];
        begin++;
        end--;
    }
}

