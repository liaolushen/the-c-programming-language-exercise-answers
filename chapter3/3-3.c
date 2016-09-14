#include <stdio.h>


void expand(char s1[], char s2[]);


int main() {
    char a1[100] = "a-b-c";
    char a2[100] = "a-z0-9";
    char a3[100] = "-0-9-";
    char b1[100], b2[100], b3[100];
    expand(a1, b1);
    expand(a2, b2);
    expand(a3, b3);
    printf("%s\n", b1);
    printf("%s\n", b2);
    printf("%s\n", b3);
}

void expand(char s1[],char s2[]) {
    int i, j, c;
    i = j = 0;

    while ((c = s1[i++]) != '\0') {
        if (s1[i] == '-' && s1[i+1] >= c) {
            i++;
            while (c < s1[i]) s2[j++] = c++;
        } else {
            s2[j++] = c;
        }
    }
    s2[j] = '\0';
}

