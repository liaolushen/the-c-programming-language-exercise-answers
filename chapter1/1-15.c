#include <stdio.h>

void fahr_to_celsius(int lower, int upper, int step);

int main() {
    fahr_to_celsius(0, 300, 20);
}

void fahr_to_celsius(int lower, int upper, int step) {
    float fahr, celsius;
    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}
