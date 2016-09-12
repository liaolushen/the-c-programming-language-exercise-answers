#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
int htoi(char s[]);

int main() {
    char line[MAXLINE];
    while (get_line(line, MAXLINE)) {
        printf("%d\n", htoi(line));
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


int htoi(char s[]) {
    int i, result;
    result = 0;
    for (i = 0; s[i] != '\0' && s[i] != '\n'; i++) {
        if (i == 0 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
            i = 1;
            continue;
        }

        result *= 16;
        if (s[i] >= '0' && s[i] <= '9') result += s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f') result += s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F') result += s[i] - 'A' + 10;
    }
    return result;
}
