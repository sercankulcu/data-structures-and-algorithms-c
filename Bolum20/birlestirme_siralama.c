/* Birlestirme siralamasi (mergesort) ve iki uctan birlestirme (merge): sol
 * yari b'ye oldugu gibi, sag yari ters kopyalanir; her yari otekinin bekcisi
 * olur. Yardimci dizi b bir kez ayrilir (notlardaki birlestirme_sirala).
 * Ornekler notlardan: merge(a, b, 0, 2, 6) ile [3, 5, 7 | 4, 5, 6, 10] ve
 * mergesort ile [89, 67, 59, 62, 23, 93, 24, 20, 28, 60].
 * Slaytlar: "Birlestirme Siralamasi" (iki slayt), "merge() Adim Adim",
 * "mergesort() Adim Adim". */
#include <stdio.h>   /* sunumda yok */
#include <stdlib.h>  /* sunumda yok: malloc, free */

/* sunumda yok: makro Bolum 19 "Ortak Altyapi: Makrolar" slaytindan */
#define kucuk(A, B) ((A) < (B))

/* sunumda ikinci slaytta; mergesort'tan once tanimlanmali */
void merge(int a[], int b[], int L, int m, int R) {
    int i, j, k;
    for (i = m + 1; i > L; i--) b[i - 1] = a[i - 1];
    for (j = m; j < R; j++) b[R + m - j] = a[j + 1];
    for (k = L; k <= R; k++)
        if (kucuk(b[j], b[i]))
            a[k] = b[j--];
        else
            a[k] = b[i++];
}

void mergesort(int a[], int b[], int L, int R) {
    if (R <= L) return;
    int m = (R + L) / 2;
    mergesort(a, b, L, m);
    mergesort(a, b, m + 1, R);
    merge(a, b, L, m, R);
}

/* sunumda yok: ders notundaki sarmalayici, b'yi bir kez ayirir */
int birlestirme_sirala(int a[], int n) {
    int *b = malloc(n * sizeof *b);   /* a ile aynı boyda */
    if (b == NULL) return 0;          /* bellek yok: sıralanmadı */
    mergesort(a, b, 0, n - 1);
    free(b);
    return 1;
}

/* sunumda yok: diziyi yazdirir */
static void yazdir(const char *ad, const int a[], int n) {
    printf("%s", ad);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* sunumda yok */
    int a[] = {3, 5, 7, 4, 5, 6, 10};
    int b[7];
    merge(a, b, 0, 2, 6);
    yazdir("merge:    ", a, 7);
    yazdir("b:        ", b, 7);   /* kopyadan sonra: sol artan, sag ters */

    int c[] = {89, 67, 59, 62, 23, 93, 24, 20, 28, 60};
    if (!birlestirme_sirala(c, 10)) return 1;
    yazdir("mergesort:", c, 10);
    return 0;
}

/* Beklenen cikti:
 * merge:     3 4 5 5 6 7 10
 * b:         3 5 7 10 6 5 4
 * mergesort: 20 23 24 28 59 60 62 67 89 93
 */
