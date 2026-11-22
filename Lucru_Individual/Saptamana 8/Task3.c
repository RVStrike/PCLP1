#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void procesare(char *s) {
    char *c = strdup(s);
    char *end;
    char *p = strtok(c, ":");
    for(;;) {
        float medie = 0;
        int count = 0;
        printf("%s: ", p);
        p = strtok(NULL, ";");
        for (;;) {
            float n = strtof(p, &end);
            medie += n;
            count ++;

            if(*end == ',') {
                end ++;
            }
            else {
                printf("%.2f\n", medie/count);
                break;
            }

            p = end;
        }
        p = strtok(NULL, ":");
        if (p == NULL) {
            break;
        }

    }
    free(c);
}

int main() {
    char c[100] = {"ana:8,10;dan:7,9;ioana:10"};
    procesare(c);
    return 0;
}
