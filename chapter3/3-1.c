#include <stdio.h>


int binsearch(int x, int v[], int n);

int main() {
    int x = 12, n = 10;
    int v[10] = {2, 3, 7, 10, 11, 12, 15, 18, 20, 21};
    printf("binsearch result: %d\n", binsearch(x, v, n));
    return 0;
}

int binsearch(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return v[low] == x ? low : -1;
}
