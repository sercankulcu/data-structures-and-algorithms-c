/* Sinav sorusundaki bagli birlestirme siralamasi: iki ozyinelemeli cagri
 * merge'un argumanlaridir, hangisinin once calisacagi C'de belirtilmemistir.
 * Ara bag degerleri derleyiciye gore degisebilir, sonuc listesi degismez.
 * Ornek, notlardaki anahtarlar a[1..9] = 42, 7, 18, -5, 27, 11, 55, 83, 30
 * (soru kagidindaki ? yerine 42, 7 ve 55); sonuc listesinin basi 4.
 * Slayt: "Sinav Sorusu: Bagli Merge Sort". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: eleman "Alfabetik Verileri Siralamak" slaytindan */
typedef struct {
    int anahtar;   /* + büyük veri alanları */
    int bag;       /* sonraki öğenin indisi, 0 = son */
} eleman;

/* sunumda yok: merge "Bagli merge Adim Adim" slaytindan */
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

int mergesort(eleman a[], int L, int R) {
    int m;
    if (R <= L) return L;
    m = (R + L) / 2;
    return merge(a, mergesort(a, m + 1, R),
                    mergesort(a, L, m));
}

int main(void) {   /* sunumda yok */
    int anahtarlar[] = {42, 7, 18, -5, 27, 11, 55, 83, 30};
    eleman a[10];
    a[0].anahtar = 0;                      /* kullanilmaz */
    a[0].bag = 0;
    for (int k = 1; k <= 9; k++) {
        a[k].anahtar = anahtarlar[k - 1];
        a[k].bag = 0;
    }

    int bas = mergesort(a, 1, 9);
    printf("bas = %d\n", bas);
    printf("liste:");
    for (int p = bas; p; p = a[p].bag) printf(" %d", a[p].anahtar);
    printf("\n");
    printf("bag[1..9]:");
    for (int k = 1; k <= 9; k++) printf(" %d", a[k].bag);
    printf("\n");
    return 0;
}

/* Beklenen cikti:
 * bas = 4
 * liste: -5 7 11 18 27 30 42 55 83
 * bag[1..9]: 7 6 5 2 9 3 8 0 1
 */
