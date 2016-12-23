#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int c;
    if (strcmp(argv[0], "./lower") == 0) {
        while ((c = getchar()) != EOF)
            putchar(tolower(c));
    } else {
        while ((c = getchar()) != EOF)
            putchar(toupper(c));
    }
    return 0;
}
