#include <stdio.h>

int main() {
    float fahr, celsius;
    int lower, upper, step;
    lower = 0; /* 摄氏度的下限 */
    upper = 300; /* 摄氏度的上限 */
    step = 20;

    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius * (9.0/5.0) + 32.0;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
}

