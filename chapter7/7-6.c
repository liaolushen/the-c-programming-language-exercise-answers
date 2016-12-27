#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char const *argv[]) {
    FILE *fp1, *fp2;
    char line1[MAXLINE], line2[MAXLINE];
    if (argc != 3) {
        fprintf(stderr, "argc error!\n");
    } else {
        if ((fp1 = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", argv[0], argv[1]);
            exit(1);
        } else if ((fp2 = fopen(argv[2], "r")) == NULL) {
            fprintf(stderr, "%s: can't open %s\n", argv[0], argv[2]);
            exit(1);
        } else {
            int line_num = 1;
            fgets(line1, MAXLINE, fp1);
            while ((fgets(line1, MAXLINE, fp1) != NULL) && (fgets(line2, MAXLINE, fp2) != NULL)) {
                if (strcmp(line1, line2) != 0) {
                    fprintf(stdout, "%s %d: %s", argv[1], line_num, line1);
                    fprintf(stdout, "%s %d: %s", argv[2], line_num, line2);
                    break;
                }
                line_num++;
            }
            fclose(fp1);
            fclose(fp2);
        }
    }
    return 0;
}
