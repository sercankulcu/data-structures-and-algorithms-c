/* Hizli siralama (quicksort1) ve bolumleme (bol). bol, pivot v = a[R]'yi
 * sirali dizide duracagi konuma koyar ve bu konumu dondurur. Ornek, notlardaki
 * [37, 15, 24, 33, 49, 11, 51, 77, 72, 48]: once tek bir bol(a, 0, 9) cagrisi,
 * sonra ayni dizinin quicksort1 ile tamamen siralanmasi.
 * Slaytlar: "Hizli Siralama", "Bolumleme Degismezi", "bol() Adim Adim",
 * "quicksort1() Adim Adim". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: makrolar Bolum 19 "Ortak Altyapi: Makrolar" slaytindan */
#define kucuk(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

int bol(int a[], int L, int R);

void quicksort1(int a[], int L, int R) {
    if (R <= L) return;
    int i = bol(a, L, R);
    quicksort1(a, L, i - 1);
    quicksort1(a, i + 1, R);
}

int bol(int a[], int L, int R) {
    int i = L - 1, j = R, v = a[R]; // pivot a[R]
    for (;;) {
        while (kucuk(a[++i], v))
            ;
        while (kucuk(v, a[--j]))
            if (j == L) break;
        if (i >= j) break;
        SWAP(a[i], a[j]);
    }
    SWAP(a[i], a[R]);
    return i;
}

/* sunumda yok: diziyi yazdirir */
static void yazdir(const int a[], int n) {
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* sunumda yok */
    int a[] = {37, 15, 24, 33, 49, 11, 51, 77, 72, 48};
    int i = bol(a, 0, 9);
    printf("bol(a, 0, 9) = %d:", i);
    yazdir(a, 10);

    int b[] = {37, 15, 24, 33, 49, 11, 51, 77, 72, 48};
    quicksort1(b, 0, 9);
    printf("quicksort1:");
    yazdir(b, 10);
    return 0;
}

/* Beklenen cikti:
 * bol(a, 0, 9) = 5: 37 15 24 33 11 48 51 77 72 49
 * quicksort1: 11 15 24 33 37 48 49 51 72 77
 */
