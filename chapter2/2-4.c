#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int maxline);
void squeeze(char s1[], char s2[]);

int main() {
    char s1[MAXLINE], s2[MAXLINE];
    while (get_line(s1, MAXLINE) && get_line(s2, MAXLINE)) {
        squeeze(s1, s2);
        printf("%s\n", s1);
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


void squeeze(char s1[], char s2[]) {
    int i, j, k;
    for (i = j = 0; s1[i] != '\0'; i++) {
        for (k = 0; s2[k] != '\0'; k++) {
            if (s1[i] == s2[k]) break;
        }
        if (s2[k] == '\0') s1[j++] = s1[i];
    }
    s1[j] = '\0';
}
