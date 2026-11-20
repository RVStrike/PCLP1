#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

double durata_secunde(const char* c, double *out) {
    errno = 0;
    char *end;
    double i = strtof(c, &end);
    if (c==end) {
        return 1; //lipsa numar
    }
    c = end;
    if (strcmp(c, "h") == 0) {
        *out = i * 3600;
    }
    else if (strcmp(c, "min") == 0) {
        *out = i * 60;
    }
    else if (strcmp(c, "s") == 0) {
        *out = i;
    }
    else if (strcmp(c, "ms") == 0) {
        *out = i / 1000;
    }
    else  {
        return 2; //unitate necunoscuta
    }

    return 0;
}

int main(void) {
    double n;
    char* c = malloc(15 * sizeof(char));

    if(c == NULL) {
        printf("Nu a mers alocarea");
        return 1;
    }

    scanf("%s", c);

    int r = durata_secunde(c, &n);

    free(c);

    switch(r) {
        case 0:
            printf("Number of seconds %f s", n );
            break;
        case 1:
            printf("Nu exista numar");
            break;
        case 2:
            printf("Unitate de timp necunoscuta");
            break;
        default:
            printf("Default");
            return 1;
    }

    return 0;

}
