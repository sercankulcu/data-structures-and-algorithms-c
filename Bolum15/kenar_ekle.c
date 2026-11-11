/* Komsuluk listesi bildirimi ve kenar_ekle: her kenar listenin basina O(1)'de
 * girer, bu yuzden listeler gelis sirasinin tersidir. Notlardaki ornek:
 * ucgenin kenarlari (0,1), (0,2), (1,2) bu sirayla eklenir.
 * Slaytlar: "Komsuluk Listesi", "Liste Kurma Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_DUGUM 50   /* en fazla dugum sayisi */
typedef struct oge *oge_gost;
typedef struct oge {
    int dugum;         /* komsu dugumun numarasi */
    oge_gost bag;      /* listedeki sonraki komsu */
} oge;                 /* ';' ve typedef adi unutulmamali */
oge_gost baslik[MAX_DUGUM];   /* her dugume bir liste */

void kenar_ekle(int u, int v)   /* u -> v */
{
    oge_gost p = malloc(sizeof(oge));
    if (p == NULL) exit(1);       /* bellek yok */
    p->dugum = v;
    p->bag = baslik[u];   /* basa ekle: O(1) */
    baslik[u] = p;
}

/* sunumda yok: ders notundaki listeleri_birak */
void listeleri_birak(oge_gost bas[], int n)
{
    int i;
    oge_gost p;
    for (i = 0; i < n; i++) {
        while (bas[i]) {
            p = bas[i];
            bas[i] = p->bag;   /* once bag saklanir */
            free(p);
        }
    }
}

/* sunumda yok: listeleri yazar */
static void listeleri_yaz(int n)
{
    int i;
    oge_gost p;
    for (i = 0; i < n; i++) {
        printf("baslik[%d]:", i);
        for (p = baslik[i]; p; p = p->bag)
            printf(" %d", p->dugum);
        printf("\n");
    }
}

int main(void)
{
    /* yonsuz her kenar iki cagriyla eklenir */
    kenar_ekle(0, 1);  kenar_ekle(1, 0);
    kenar_ekle(0, 2);  kenar_ekle(2, 0);
    kenar_ekle(1, 2);  kenar_ekle(2, 1);
    listeleri_yaz(3);
    listeleri_birak(baslik, 3);
    return 0;
}

/* Beklenen cikti:
 * baslik[0]: 2 1
 * baslik[1]: 2 0
 * baslik[2]: 1 0
 */
