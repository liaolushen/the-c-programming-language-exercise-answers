#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
int any(char s1[], char s2[]);

int main() {
    char s1[MAXLINE], s2[MAXLINE];
    while (get_line(s1, MAXLINE) && get_line(s2, MAXLINE)) {
        printf("%d\n", any(s1, s2));
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


int any(char s1[], char s2[]) {
    int i, j, pos;
    pos = -1;
    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j]) break;
        }
        if (s2[j] != '\0' && s2[j] != '\n') {
            pos = i;
            break;
        }
    }
    return pos;
}
