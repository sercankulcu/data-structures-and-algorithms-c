/* Iki listeyi birlestirmek: L1'in son dugumu bulunur ve L2'ye baglanir.
 * Notlardaki ornek: L1 = 1 -> 4, L2 = 6 -> 9; sonuc 1 -> 4 -> 6 -> 9.
 * Bos L1 ile cagri L2'yi dondurur.
 * Slayt: "Iki Listeyi Birlestirme". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

// L1'in sonuna L2'yi bağlar, başı döndürür
oge_gost birlestir(oge_gost L1, oge_gost L2) {
    oge_gost p;
    if (L1 == NULL) return L2;
    if (L2 != NULL) {
        for (p = L1; p->bag != NULL; p = p->bag)
            ;                   // L1'in son düğümü
        p->bag = L2;
    }
    return L1;
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

/* sunumda yok: "Gezinme" slaytindaki yazdir */
void yazdir(oge_gost p) {
    for (; p != NULL; p = p->bag)
        printf("%d ", p->deger);
    printf("\n");
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
    int a[] = {1, 4};
    int b[] = {6, 9};
    oge_gost L1 = liste_kur(a, 2);
    oge_gost L2 = liste_kur(b, 2);
    oge_gost L = birlestir(L1, L2);
    yazdir(L);
    L = birlestir(NULL, L);           /* bos L1 */
    yazdir(L);
    liste_bosalt(&L);                 /* L1 ve L2'nin dugumleri artik tek listede */
    return 0;
}

/* Not: her satirin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 1 4 6 9
 * 1 4 6 9
 */
