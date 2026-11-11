/* Ters (transpoz) komsuluk listesi: her <i,j> kenari ters[j] listesine i
 * olarak eklenir. Notlardaki ornek: G3, bas[0] = 1, bas[1] = 0 -> 2,
 * bas[2] = NULL.
 * Slayt: "Transpoz Liste Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_DUGUM 50   /* en fazla dugum sayisi */
typedef struct oge *oge_gost;
typedef struct oge {
    int dugum;         /* komsu dugumun numarasi */
    oge_gost bag;      /* listedeki sonraki komsu */
} oge;                 /* ';' ve typedef adi unutulmamali */
oge_gost baslik[MAX_DUGUM];   /* her dugume bir liste */

/* sunumda yok: ders notundaki ekle (kenar_ekle'nin her baslik dizisinde
 * calisan bicimi) */
void ekle(oge_gost bas[], int u, int v)   /* bas[u] listesine v */
{
    oge_gost p = malloc(sizeof(oge));
    if (p == NULL) exit(1);
    p->dugum = v;
    p->bag = bas[u];
    bas[u] = p;
}

void devrik_kur(oge_gost bas[], oge_gost ters[],
               int n)
{
    int i;
    oge_gost p;
    for (i = 0; i < n; i++) ters[i] = NULL;
    for (i = 0; i < n; i++)
        for (p = bas[i]; p; p = p->bag)
            ekle(ters, p->dugum, i);  /* <j,i> */
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
static void yaz(const char *ad, oge_gost bas[], int n)
{
    int i;
    oge_gost p;
    for (i = 0; i < n; i++) {
        printf("%s[%d]:", ad, i);
        for (p = bas[i]; p; p = p->bag)
            printf(" %d", p->dugum);
        printf("\n");
    }
}

int main(void)
{
    oge_gost ters[MAX_DUGUM];
    /* G3: <0,1>, <1,0>, <1,2>; basa eklendigi icin 1'in listesi 0 -> 2 */
    ekle(baslik, 0, 1);
    ekle(baslik, 1, 2);
    ekle(baslik, 1, 0);
    devrik_kur(baslik, ters, 3);
    yaz("bas", baslik, 3);
    yaz("ters", ters, 3);
    listeleri_birak(baslik, 3);
    listeleri_birak(ters, 3);
    return 0;
}

/* Beklenen cikti:
 * bas[0]: 1
 * bas[1]: 0 2
 * bas[2]:
 * ters[0]: 1
 * ters[1]: 0
 * ters[2]: 1
 */
