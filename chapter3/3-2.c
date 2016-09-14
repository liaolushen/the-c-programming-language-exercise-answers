#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);

int main() {
    char a[100] = "hello\tworld\n";
    char b[100];
    printf("%s", a);
    escape(b, a);
    printf("%s", b);
    unescape(a, b);
    printf("%s", a);
}


void escape(char s[], char t[]) {
    int si, ti;
    si = 0;
    ti = 0;
    while (t[ti] != '\0') {
        switch(t[ti]) {
            case '\n':
                s[si++] = '\\';
                s[si++] = 'n';
                ti++;
                break;
            case '\t':
                s[si++] = '\\';
                s[si++] = 't';
                ti++;
                break;
            default:
                s[si++] = t[ti++];
                break;
        }
    }
    s[si] = t[ti];
}


void unescape(char s[], char t[]) {
    int si, ti;
    while (t[ti] != '\0') {
        switch(t[ti]) {
            case '\\':
                if (t[ti + 1] == 'n') {
                    s[si++] = '\n';
                    ti += 2;
                } else if (t[ti + 1] == 't') {
                    s[si++] = '\t';
                    ti += 2;
                } else {
                    s[si++] = t[ti++];
                }
                break;
            default:
                s[si++] = t[ti++];
        }
    }
}

