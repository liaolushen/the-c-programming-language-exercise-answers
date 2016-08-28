#include <stdio.h>

int main() {
    float fahr, celsius;
    int lower, upper, step;
    lower = 0; /* 华氏度的下限 */
    upper = 300; /* 华氏度的上限 */
    step = 20;

    fahr = lower;
    printf("TRANSLATE\n");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}

