#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main() {
    printf("%f\n", atof("11234234430.123e-10"));
}

double atof(char s[]) {
    double val, power, index_power, index_sign;
    int i, sign, index;

    for (i = 0; isspace(s[i]); i++);
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') i++;

    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.') i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if (s[i] == 'e') i++;
    index_sign = (s[i] == '-') ? 0.1 : 10.0;
    if (s[i] == '+' || s[i] == '-') i++;


    for (index = 0; isdigit(s[i]); i++) {
        index = 10 * index + (s[i] - '0');
    }

    index_power = 1.0;
    while (index--) index_power *= index_sign;

    return (sign * val / power) * index_power;
}
