#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};



int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
    int yearday = day_of_year(2016, 4, 5);
    printf("%d\n", yearday);
    int month, day;
    month_day(2016, yearday, &month, &day);
    printf("%d月%d日\n", month, day);
}

int day_of_year(int year, int month, int day) {
    int i, leap;
    if (year <= 0) {
        printf("error: year wrong");
    }

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (month <= 0 || month > 12) {
        printf("error: month wrong");
    }

    
    if (day <= 0 || day > daytab[leap][month]) {
        printf("error: day wrong");
    }

    for (i = 1; i < month; i++) {
        day += *(daytab[leap] + i);
    }

    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    if (year <= 0) {
        printf("error: year wrong");
    }

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

    if (yearday > 365 + leap || year <= 0) {
        printf("error: yearday wrong");
    }
    for (i = 1; yearday > *(daytab[leap]+i); i++) yearday -= *(daytab[leap]+i);
    *pmonth = i;
    *pday = yearday;
}
