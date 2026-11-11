/* Gelistirilmis hizli siralama (quicksort3): pivot ucun ortancasi (a[L],
 * orta, a[R]) olarak secilir, M'den kucuk parcalar siralanmadan birakilir ve
 * sirala sonunda tek bir eklemeli siralama gecisi yapar. Ornek, notlardaki
 * izleme: [8, 3, 5, 1, 9, 2, 7, 6, 4] ve M = 3. quicksort3'ten sonra dizi
 * neredeyse siralidir; insertion kalan iki cifti duzeltir.
 * Slaytlar: "Gelistirilmis Quick Sort", "quicksort3() Adim Adim". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: makrolar Bolum 19 "Ortak Altyapi: Makrolar" slaytindan */
#define kucuk(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

/* sunumda yok: bol "Bolumleme Degismezi" slaytindan */
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

/* sunumda yok: insertion Bolum 19 "Eklemeli Siralama" slaytindan */
void insertion(int a[], int L, int R) {
    for (int i = L + 1; i <= R; i++) {
        int v = a[i];      // yerleştirilecek
        int j = i - 1;     // a[L..i-1] sıralı
        while (j >= L && a[j] > v) {
            a[j + 1] = a[j]; // sağa kaydır
            j--;
        }
        a[j + 1] = v;
    }
}

/* sunumda M 10; notlardaki izleme (Tablo 20.7) M = 3 kullanir. M = 10 ile bu
 * dokuz ogelik dizide quicksort3 hemen doner ve butun isi insertion yapar. */
#define M 3     /* bu boydan küçük parça kalsın */
void quicksort3(int a[], int L, int R) {
    if (R - L <= M) return;
    SWAP(a[(L + R) / 2], a[R - 1]);
    if (a[R-1] < a[L]) SWAP(a[R-1], a[L]); // a[L] <= a[R-1]
    if (a[R] < a[L]) SWAP(a[R], a[L]);     // a[L] <= a[R]
    if (a[R] < a[R-1]) SWAP(a[R], a[R-1]); // a[R-1] <= a[R]
    int i = bol(a, L + 1, R - 1);
    quicksort3(a, L, i - 1);
    quicksort3(a, i + 1, R);
}
void sirala(int a[], int L, int R) {
    quicksort3(a, L, R);
    insertion(a, L, R);   /* kalan küçük parçalar */
}

/* sunumda yok: diziyi yazdirir */
static void yazdir(const char *ad, const int a[], int n) {
    printf("%s", ad);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* sunumda yok */
    int a[] = {8, 3, 5, 1, 9, 2, 7, 6, 4};
    quicksort3(a, 0, 8);           /* sirala'nin ilk adimi tek basina */
    yazdir("quicksort3:", a, 9);

    int b[] = {8, 3, 5, 1, 9, 2, 7, 6, 4};
    sirala(b, 0, 8);
    yazdir("sirala:    ", b, 9);
    return 0;
}

/* Beklenen cikti:
 * quicksort3: 1 3 2 4 6 5 7 8 9
 * sirala:     1 2 3 4 5 6 7 8 9
 */
