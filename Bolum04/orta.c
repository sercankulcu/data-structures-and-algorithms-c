/* Orta dugumu tek geciste bulmak: yavas isaretci bir, hizli isaretci iki
 * adim ilerler. Notlardaki ornek: 1 -> 2 -> 3 -> 4 -> 5 listesinde orta 3;
 * cift uzunlukta (1 -> 2 -> 3 -> 4) ikinci orta (3) doner.
 * Slayt: "Orta Dugumu Bulma". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

oge_gost orta(oge_gost bas) {
    oge_gost yavas = bas, hizli = bas;
    while (hizli != NULL && hizli->bag != NULL) {
        yavas = yavas->bag;        // 1 adım
        hizli = hizli->bag->bag;   // 2 adım
    }
    return yavas;
}

/* sunumda yok: diziden liste kurar (sona ekleyerek) */
static oge_gost liste_kur(const int a[], int n) {
    oge_gost bas = NULL, *son = &bas;
    for (int i = 0; i < n; i++) {
        oge_gost p = malloc(sizeof *p);
        if (p == NULL) exit(1);
        p->deger = a[i];
        p->bag = NULL;
        *son = p;
        son = &p->bag;
    }
    return bas;
}

/* sunumda yok: listeyi bellege iade eder */
static void liste_bosalt(oge_gost *list) {
    while (*list != NULL) {
        oge_gost p = *list;
        *list = p->bag;
        free(p);
    }
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    oge_gost tek = liste_kur(a, 5);
    oge_gost cift = liste_kur(a, 4);
    printf("orta(1..5) = %d\n", orta(tek)->deger);
    printf("orta(1..4) = %d\n", orta(cift)->deger);
    liste_bosalt(&tek);
    liste_bosalt(&cift);
    return 0;
}

/* Beklenen cikti:
 * orta(1..5) = 3
 * orta(1..4) = 3
 */
