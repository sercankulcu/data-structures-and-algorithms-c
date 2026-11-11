/* Bagli (indisli) birlestirme siralamasi: kayitlar yerinden oynamaz, her
 * kaydin bag alani sonraki ogenin indisini tutar (0 = son). Veriler a[1..n]'de,
 * a[0] merge'de gecici bastir. Ornek, notlardaki anahtarlar
 * a[1..10] = 71, 77, 122, 38, 119, 41, 22, 115, 43, 13; sonuc listesinin basi 10.
 * Slaytlar: "Alfabetik Verileri Siralamak", "Bagli merge Adim Adim". */
#include <stdio.h>   /* sunumda yok */

typedef struct {
    int anahtar;   /* + büyük veri alanları */
    int bag;       /* sonraki öğenin indisi, 0 = son */
} eleman;

int merge(eleman a[], int birinci, int ikinci);   /* sunumda yok: prototip */

int mergesort(eleman a[], int L, int R) {
    if (R <= L) return L;          /* tek öğeli liste */
    int m = (R + L) / 2;
    int sag = mergesort(a, m + 1, R);
    int sol = mergesort(a, L, m);
    return merge(a, sol, sag);     /* baş indisi */
}

int merge(eleman a[], int birinci, int ikinci) {
    int sonuc = 0;              // a[0]: geçici baş
    int i1 = birinci, i2 = ikinci;
    while (i1 && i2)
        if (a[i1].anahtar <= a[i2].anahtar) {
            a[sonuc].bag = i1; sonuc = i1;
            i1 = a[i1].bag;
        } else {
            a[sonuc].bag = i2; sonuc = i2;
            i2 = a[i2].bag;
        }
    a[sonuc].bag = i1 ? i1 : i2;
    return a[0].bag;
}

int main(void) {   /* sunumda yok */
    int anahtarlar[] = {71, 77, 122, 38, 119, 41, 22, 115, 43, 13};
    eleman a[11];
    a[0].anahtar = 0;                      /* kullanilmaz */
    a[0].bag = 0;
    for (int k = 1; k <= 10; k++) {
        a[k].anahtar = anahtarlar[k - 1];
        a[k].bag = 0;                      /* her oge tek basina bir liste */
    }

    int bas = mergesort(a, 1, 10);
    printf("bas = %d\n", bas);
    printf("liste:");
    for (int p = bas; p; p = a[p].bag) printf(" %d", a[p].anahtar);
    printf("\n");
    printf("bag[1..10]:");
    for (int k = 1; k <= 10; k++) printf(" %d", a[k].bag);
    printf("\n");
    return 0;
}

/* Beklenen cikti:
 * bas = 10
 * liste: 13 22 38 41 43 71 77 115 119 122
 * bag[1..10]: 2 8 0 6 3 9 4 5 1 7
 */
