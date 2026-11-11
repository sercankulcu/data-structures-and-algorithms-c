/* Verilen dugumden sonra gelen dugumu silmek: adresi tut, bagi duzelt,
 * free et. Notlardaki ornek: 5 -> 3 -> 8 -> 2 listesinde 3'ten sonrakini
 * (8) silmek; ardindan son dugumden sonrakini silmeye calismak (bir sey olmaz).
 * Slayt: "Silme: Sonrakini Sil". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

// onceki'den sonra gelen düğümü listeden ve
// bellekten siler
void sonrakini_sil(oge_gost onceki) {
    oge_gost silinecek = onceki->bag; // adresi tut
    if (silinecek == NULL) return; // silinecek yok
    onceki->bag = silinecek->bag;  // bağı düzelt
    free(silinecek);               // kalıntıyı sil
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
    int a[] = {5, 3, 8, 2};
    oge_gost liste = liste_kur(a, 4);
    yazdir(liste);
    sonrakini_sil(liste->bag);            /* 3'ten sonraki: 8 */
    yazdir(liste);
    sonrakini_sil(liste->bag->bag);       /* 2 son dugum: silinecek yok */
    yazdir(liste);
    liste_bosalt(&liste);
    return 0;
}

/* Not: her satirin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 5 3 8 2
 * 5 3 2
 * 5 3 2
 */
