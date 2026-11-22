#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *replace_all(const char *s, const char *vechi, const char *nou) {
    char *p = malloc(strlen(s)+1);
    p[0] = '\0';
    for(;;) {
        char *schimb = strstr(s, vechi);
        if (schimb == NULL) {
            strcat(p, s);
            break;
        }
        p = strncat(p, s, schimb-s);
        p = strcat(p, nou);
        s = schimb + strlen(vechi);

    }
    return p;
}

int main () {
    char *s, *vechi, *nou;
    int size_s, size_vechi, size_nou;
    printf("Size of s: ");
    scanf("%d", &size_s);
    printf("Size of vechi: ");
    scanf("%d", &size_vechi);
    printf("Size of nou: ");
    scanf("%d", &size_nou);
    s = malloc(size_s * sizeof(char) + 1);
    vechi = malloc(size_vechi * sizeof(char) + 1);
    nou = malloc (size_nou * sizeof(char) + 1);
    if (s == NULL || vechi == NULL || nou == NULL) {
        printf("Allocation failed");
        return 1;
    }

    printf("String a: ");
    scanf("%s", s);
    printf("Strng vechi: ");
    scanf("%s", vechi);
    printf("String nou: ");
    scanf("%s", nou);

    char *rez = replace_all(s, vechi, nou);

    free(s);

    printf("%s", rez);

    free(rez);

    return 0;
}
