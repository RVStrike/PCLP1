#include <stdio.h>
#include <stdlib.h>

int f1(char **addr_p) {
    int cap = 16, len = 0;
    char *str = (char *)malloc(cap * sizeof(char));
    if (!str) return -1;

    int ch;
    // Citim caracter cu caracter pana la '\n' sau EOF
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (len + 2 >= cap) { // +2 pentru '\n' si '\0'
            cap *= 2;
            char *temp = (char *)realloc(str, cap * sizeof(char));
            if (!temp) {
                free(str);
                return -1;
            }
            str = temp;
        }
        str[len++] = (char)ch;
    }
    str[len++] = '\n';
    str[len] = '\0';

    // Alocam vectori pentru vocale si consoane (maxim len elemente fiecare)
    char *v = (char *)malloc(len * sizeof(char));
    char *c = (char *)malloc(len * sizeof(char));
    int nv = 0, nc = 0;

    // Separam vocalele de consoane
    for (int i = 0; str[i] != '\n'; i++) {
        char ch_curr = str[i];
        if ((ch_curr >= 'A' && ch_curr <= 'Z') || (ch_curr >= 'a' && ch_curr <= 'z')) {
            if (ch_curr == 'a' || ch_curr == 'e' || ch_curr == 'i' || ch_curr == 'o' || ch_curr == 'u' ||
                ch_curr == 'A' || ch_curr == 'E' || ch_curr == 'I' || ch_curr == 'O' || ch_curr == 'U') {
                v[nv++] = ch_curr;
            } else {
                c[nc++] = ch_curr;
            }
        }
    }

    // Sortam vocalele (Insertion Sort)
    for (int i = 1; i < nv; i++) {
        char comp = v[i];
        int j = i - 1;
        while (j >= 0 && comp < v[j]) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = comp;
    }

    // Sortam consoanele (Insertion Sort)
    for (int i = 1; i < nc; i++) {
        char comp = c[i];
        int j = i - 1;
        while (j >= 0 && comp < c[j]) {
            c[j + 1] = c[j];
            j--;
        }
        c[j + 1] = comp;
    }

    // Reconstruim sirul pastrand pozitiile
    int iv = 0, ic = 0;
    for (int i = 0; str[i] != '\n'; i++) {
        char ch_curr = str[i];
        if ((ch_curr >= 'A' && ch_curr <= 'Z') || (ch_curr >= 'a' && ch_curr <= 'z')) {
            if (ch_curr == 'a' || ch_curr == 'e' || ch_curr == 'i' || ch_curr == 'o' || ch_curr == 'u' ||
                ch_curr == 'A' || ch_curr == 'E' || ch_curr == 'I' || ch_curr == 'O' || ch_curr == 'U') {
                str[i] = v[iv++];
            } else {
                str[i] = c[ic++];
            }
        }
    }

    free(v);
    free(c);

    // Setam adresa sirului sortat prin pointerul addr_p
    *addr_p = str;

    // Returnam diferenta in valoare absoluta
    int diff = nc - nv;
    return (diff >= 0) ? diff : -diff;
}

int main() {
    char *p = NULL;
    int k = f1(&p);
    if (p != NULL) {
        printf("k = %d, p = %s", k, p);
        free(p);
    }
    return 0;
}
