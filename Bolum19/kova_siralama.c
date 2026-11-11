/* Kova siralamasi (bucket_sort): [0, 1) araligindaki n gercel sayi n kovaya
 * dagitilir; her kova bagli bir listedir ve sayi kovasina sirali eklenir
 * (isaretcinin isaretcisiyle). Dugumler tek bir havuz dizisinden alinir.
 * Ornek, notlardaki 10 sayilik girdi.
 * Slayt: "Kova Siralama C Kodu". */
#include <stdio.h>   /* sunumda yok */
#include <stdlib.h>  /* sunumda yok: calloc, malloc, free */

typedef struct kdugum { double x; struct kdugum *bag; } kdugum;

int bucket_sort(double a[], int n) {        /* 0 <= a[i] < 1 */
    kdugum **kova = calloc(n, sizeof *kova);
    kdugum *havuz = malloc(n * sizeof *havuz);
    if (!kova || !havuz) { free(kova); free(havuz); return -1; }
    for (int i = 0; i < n; i++) {           /* dağıt + sıralı ekle */
        kdugum **p = &kova[(int)(a[i] * n)];
        while (*p && (*p)->x <= a[i]) p = &(*p)->bag;
        havuz[i].x = a[i]; havuz[i].bag = *p; *p = &havuz[i];
    }
    int k = 0;                              /* kovaları birleştir */
    for (int b = 0; b < n; b++)
        for (kdugum *q = kova[b]; q; q = q->bag) a[k++] = q->x;
    free(kova); free(havuz);
    return 0;
}

int main(void) {   /* sunumda yok */
    double a[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    if (bucket_sort(a, 10) != 0) return 1;
    for (int i = 0; i < 10; i++) printf("%.2f ", a[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti (sonda bosluk var):
 * 0.12 0.17 0.21 0.23 0.26 0.39 0.68 0.72 0.78 0.94 
 */
