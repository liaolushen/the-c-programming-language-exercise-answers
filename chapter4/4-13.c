#include <stdio.h>

void reverse(char s[]);

int main() {
    char s1[] = "hello";
    reverse(s1);
    char s2[] = "world";
    reverse(s2);

    printf("%s\n", s1);
    printf("%s\n", s2);
}


void reverse(char s[]) {
    static int i;
    char c;
    if (s[i] != '\0') {
        int c_i = i;
        c = s[i++];
        reverse(s);
        s[i - c_i] = c;
        if (c_i == 0) i = 0;
    } else {
        i--;
    }
}
