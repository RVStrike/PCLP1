#include <stdio.h>
#include "bmp_io_rgb.h"
#include <stdlib.h>

void border(unsigned char ***img, int left, int right, int top, int bottom, int k) {
    for (int i = left; i <= right; i++) {
        for (int j = 0; j < k; j++) {
            img[top+j][i][0] = 255;
            img[top+j][i][1] = 0;
            img[top+j][i][2] = 0;
            img[bottom-j][i][0] = 255;
            img[bottom-j][i][1] = 0;
            img[bottom-j][i][2] = 0;
        }
    }
    
    for (int i = top; i <= bottom; i++) {
        for (int j = 0; j < k; j++) {
            img[i][left+j][0] = 255;
            img[i][left+j][1] = 0;
            img[i][left+j][2] = 0;
            img[i][right-j][0] = 255;
            img[i][right-j][1] = 0;
            img[i][right-j][2] = 0;
        }
    }
}

unsigned char ***crop(unsigned char ***img, int left, int right, int top, int bottom, int *N, int *M) {
    unsigned char ***img2;

    int N_new = bottom - top;
    int M_new = right - left;

    img2 = malloc(N_new * sizeof(unsigned char **));

    for (int i = 0; i < N_new; i++) {
        img2[i] = malloc(M_new* sizeof(unsigned char *));
    }

    for (int i = 0; i < N_new; i++) {
        for (int j = 0; j < M_new; j++) {
            img2[i][j] = malloc(3 * sizeof(unsigned char));
        }
    }

    for (int i = 0; i < N_new; i++) {
        for (int j = 0; j < M_new; j++) {
            img2[i][j][0] = img[top+i][left+j][0];
            img2[i][j][1] = img[top+i][left+j][1];
            img2[i][j][2] = img[top+i][left+j][2];

        }
    }

    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *M; j++) {
            free(img[i][j]);
        }
    }
    
    for (int i = 0; i < *N; i++) {
        free(img[i]);
    }

    free(img);

    *N = N_new;
    *M = M_new;

    return img2;

}

void recollor(unsigned char ***img, int N, int M) {

    int C;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {

            C = (img[i][j][0] + img[i][j][1] + img[i][j][2])/3;
            img[i][j][0] = C;
            img[i][j][1] = C;
            img[i][j][2] = C;

        }
    }
}

unsigned char ***instagram(unsigned char ***img, int *N, int *M) {
    unsigned char ***img2;

    int S;
    if ( *N < *M) {
        S = *M;
    }
    else {
        S = *N;
    }

    img2 = malloc(S * sizeof(unsigned char **));

    for (int i = 0; i < S; i++) {
        img2[i] = malloc(S * sizeof(unsigned char *));
    }

    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            img2[i][j] = malloc(3 * sizeof(unsigned char));
        }
    }

    int collor0 = 0, collor1 = 0, collor2 = 0;
    int collor3 = 0, collor4 = 0, collor5 = 0;

    if (*N < S) {

        for (int i = 0; i < *M; i ++) {
        collor0 += img[0][i][0];
        collor1 += img[0][i][1];
        collor2 += img[0][i][2];
        collor3 += img[*N-1][i][0];
        collor4 += img[*N-1][i][1];
        collor5 += img[*N-1][i][2];
        }

        collor0 = collor0 / *M;
        collor1 = collor1 / *M;
        collor2 = collor2 / *M;
        collor3 = collor3 / *M;
        collor4 = collor4 / *M;
        collor5 = collor5 / *M;
        
        for (int i = 0; i < (S-*N)/2; i++) {
            for (int j = 0; j < S; j++) {
                img2[i][j][0] = collor0;
                img2[i][j][1] = collor1;
                img2[i][j][2] = collor2;
                img2[S-i-1][j][0] = collor3;
                img2[S-i-1][j][1] = collor4;
                img2[S-i-1][j][2] = collor5;
            }
        }
        if((S - *N)%2 == 1) {
            for (int i = 0; i < S; i++) {
                img2[S-1-((S - *N)/2)][i][0] = collor3;
                img2[S-1-((S - *N)/2)][i][1] = collor4;
                img2[S-1-((S - *N)/2)][i][2] = collor5;
            }
        }

        for (int i = (S-*N)/2, t = 0; i < S-((S - *N)/2); i++, t++) {
            for (int j = 0; j < S; j++) {
                img2[i][j][0] = img[t][j][0];
                img2[i][j][1] = img[t][j][1];
                img2[i][j][2] = img[t][j][2];
            }
        }
    }
    else {

        for (int i = 0; i < *N; i ++) {
        collor0 += img[i][0][0];
        collor1 += img[i][0][1];
        collor2 += img[i][0][2];
        collor3 += img[i][*M-1][0];
        collor4 += img[i][*M-1][1];
        collor5 += img[i][*M-1][2];
        }

        collor0 = collor0 / *N;
        collor1 = collor1 / *N;
        collor2 = collor2 / *N;
        collor3 = collor3 / *N;
        collor4 = collor4 / *N;
        collor5 = collor5 / *N;
        
        for (int i = 0; i < S; i++) {
            for (int j = 0; j < (S-*M)/2; j++) {
                img2[i][j][0] = collor0;
                img2[i][j][1] = collor1;
                img2[i][j][2] = collor2;
                img2[i][S-j-1][0] = collor3;
                img2[i][S-j-1][1] = collor4;
                img2[i][S-j-1][2] = collor5;
            }
        }
        if((S - *M)%2 == 1) {
            for (int i = 0; i < S; i++) {
                img2[i][S-((S-1 - *M)/2)][0] = collor3;
                img2[i][S-((S-1 - *M)/2)][1] = collor4;
                img2[i][S-((S-1 - *M)/2)][2] = collor5;
            }
        }

        for (int i = 0; i < S; i++) {
            for (int j = (S-*M)/2, t = 0; j < S - ((S-*M)/2); j++, t++) {
                img2[i][j][0] = img[i][t][0];
                img2[i][j][1] = img[i][t][1];
                img2[i][j][2] = img[i][t][2];
            }
        }
    }

    for (int i = 0; i < *N; i++) {
        for (int j = 0; j < *M; j++) {
            free(img[i][j]);
        }
    }
    
    for (int i = 0; i < *N; i++) {
        free(img[i]);
    }

    free(img);

    *N = S;
    *M = S;

    return img2;
}

int main(void) {
    int N, M;
    int left, right, top, bottom, k;
    int action;
    unsigned char ***img = bmp_read("alpaca.bmp", &N, &M);
    if (!img) {
        return 1;
    }

    printf("What do you want to do\n1)Draw a border\n2)Crop the image\n3)Recollor the image\n4)Make it postable on instagram\nChose between 1-4\n");
    scanf("%d", &action);

    if (action==1) {
        printf("Write left coordonate\n");
        scanf("%d", &left);
        printf("Write right coordonate\n");
        scanf("%d", &right);
        printf("Write top coordonate\n");
        scanf("%d", &top);
        printf("Write bottom coordonate\n");
        scanf("%d", &bottom);
        printf("Write width of border\n");
        scanf("%d", &k);
        border(img, left, right, top, bottom, k);
    } else if (action==2) {
        printf("Write left coordonate\n");
        scanf("%d", &left);
        printf("Write right coordonate\n");
        scanf("%d", &right);
        printf("Write top coordonate\n");
        scanf("%d", &top);
        printf("Write bottom coordonate\n");
        scanf("%d", &bottom);
        img = crop(img, left, right, top, bottom, &N, &M);
    } else if (action==3) {
        recollor(img, N, M); 
    } else if (action==4) {
        img = instagram(img, &N, &M);
    } else {
        return 1;
    }

    bmp_write("output.bmp", img, N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            free(img[i][j]);
        }
    }
    
    for (int i = 0; i < N; i++) {
        free(img[i]);
    }

    free(img);

    return 0;
}