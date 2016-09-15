#include <stdio.h>

int strindex(char s[], char t[]);

int main() {
    printf("%d\n", strindex("abcbcde", "bc"));
}

int strindex(char s[], char t[]) {
    int s_len, t_len;
    int i, j;

    for (s_len = 0; s[s_len] != '\0'; s_len++);
    for (t_len = 0; t[t_len] != '\0'; t_len++);

    for (i = s_len - 1; i >= 0; i--) {
        for (j = 0; j < t_len; j++) {
            if (s[i - t_len + 1 + j] != t[j]) break;
        }
        if (j == t_len) return i - t_len + 1;
    }
    return -1;
}
