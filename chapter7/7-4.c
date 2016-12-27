#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int minscanf(char *fmt, ...) {
    va_list ap;
    char *p, *sval;
    int *ival;
    float *dval;

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            getchar();
            continue;
        }

        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int *);
                scanf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, float *);
                scanf("%f", dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                char c = getchar();
                for (; !isspace(c); c = getchar()) {
                    *sval++ = c;
                }
                p++;
                *sval = '\0';

                break;
            default:
                break;
        }
    }
    va_end(ap);
}


int main(int argc, char const *argv[]) {
    int day, month, year;
    char monthname[20];
    float f;
    minscanf("%d/%d/%d", &day, &month, &year);
    printf("%d/%d/%d\n", day, month, year);
    minscanf("%d %s %d", &day, monthname, &year);
    printf("%d %s %d\n", day, monthname, year);
    minscanf("%f", &f);
    printf("%f\n", f);

    return 0;
}
