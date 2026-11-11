/* Heap sort: a[1..n] dizisi tam ikili agac gibi okunur (cocuklar 2i, 2i+1).
 * Once asagidan yukariya maksimum heap kurulur, sonra kokteki en buyuk oge
 * sona alinip heap heapify ile duzeltilir. Ornek, notlardaki Horowitz dizisi
 * [26, 5, 77, 1, 61, 11, 59, 15, 48, 19]; main kurma asamasini ayrica yazar.
 * Slaytlar: "Heap Sort", "heapsort: Siralama". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: makro Bolum 19 "Ortak Altyapi: Makrolar" slaytindan */
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void heapify(int a[], int kok, int n) {
    int t = a[kok], j;
    for (j = 2 * kok; j <= n; j *= 2) {
        if (j < n && a[j] < a[j + 1]) j++; // büyük
        if (t >= a[j]) break;   // t buraya sığar
        a[j / 2] = a[j];        // çocuğu yukarı al
    }
    a[j / 2] = t;
}
void heapsort(int a[], int n) {     /* a[1..n] */
    int i;
    for (i = n / 2; i >= 1; i--)     /* heap kur */
        heapify(a, i, n);
    for (i = n - 1; i >= 1; i--) {   /* sırala */
        SWAP(a[1], a[i + 1]);    /* en büyüğü sona */
        heapify(a, 1, i);            /* heap'i düzelt */
    }
}

/* sunumda yok: a[1..n]'yi yazdirir */
static void yazdir(const char *ad, const int a[], int n) {
    printf("%s", ad);
    for (int i = 1; i <= n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* sunumda yok */
    /* a[0] kullanilmaz */
    int h[] = {0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    for (int i = 10 / 2; i >= 1; i--)   /* heapsort'un kurma asamasi */
        heapify(h, i, 10);
    yazdir("heap:    ", h, 10);

    int a[] = {0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19};
    heapsort(a, 10);
    yazdir("heapsort:", a, 10);
    return 0;
}

/* Beklenen cikti:
 * heap:     77 61 59 48 19 11 26 15 1 5
 * heapsort: 1 5 11 15 19 26 48 59 61 77
 */
