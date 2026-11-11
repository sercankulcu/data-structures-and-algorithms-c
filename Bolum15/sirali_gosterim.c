/* Dizi ile sirali gosterim: ilk n + 1 hucre baslangic indisleri, kalan 2e
 * hucre komsular. i'nin komsulari dugum[dugum[i]] .. dugum[dugum[i+1] - 1].
 * Notlardaki ornek: G4 (n = 8, e = 7, 23 hucre); komsulari_yaz(dugum, 5)
 * "4 6" yazar.
 * Slayt: "Sirali Dizi Adim Adim". */
#include <stdio.h>

void komsulari_yaz(const int dugum[], int i)
{
    int k;
    for (k = dugum[i]; k < dugum[i + 1]; k++)
        printf("%d ", dugum[k]);
    printf("\n");
}

int main(void)
{
    /* sunumda yok: G4'un sirali gosterimi (Sekil 15.13) */
    static const int dugum[23] = {
        9, 11, 13, 15, 17, 18, 20, 22, 23,   /* 0..8: baslangic indisleri */
        1, 2,  0, 3,  0, 3,  1, 2,           /* 0, 1, 2, 3 */
        5,  4, 6,  5, 7,  6                  /* 4, 5, 6, 7 */
    };
    int i;
    for (i = 0; i < 8; i++) {
        printf("%d: ", i);
        komsulari_yaz(dugum, i);
    }
    return 0;
}

/* Not: komsulari_yaz her sayidan sonra bir bosluk birakir. */
/* Beklenen cikti:
 * 0: 1 2
 * 1: 0 3
 * 2: 0 3
 * 3: 1 2
 * 4: 5
 * 5: 4 6
 * 6: 5 7
 * 7: 6
 */
