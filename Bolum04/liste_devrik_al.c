/* Bagli listeyi yerinde ters cevirmek: yeni dugum ve kopya yok, yalniz
 * baglarin yonu degisir (r, q, p uc isaretci). Notlardaki ornek:
 * 10 -> 20 -> 30 listesi 30 -> 20 -> 10 olur; ikinci uygulama ilk hale
 * dondurur; bos listede bir sey olmaz.
 * Slayt: "Ters Cevirme Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

void liste_devrik_al(oge_gost *list) {
    oge_gost r, p = *list, q = NULL;
    while (p) {
        r = q;         // r, q'yu takip eder
        q = p;         // q, p'yi takip eder
        p = p->bag;    // p'yi ilerlet
        q->bag = r;    // bağı tersine çevir
    }
    *list = q;         // son öğe liste başı
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
    int a[] = {10, 20, 30};
    oge_gost liste = liste_kur(a, 3);
    oge_gost bos = NULL;
    yazdir(liste);
    liste_devrik_al(&liste);
    yazdir(liste);
    liste_devrik_al(&liste);
    yazdir(liste);
    liste_devrik_al(&bos);
    printf("bos liste: %s\n", bos == NULL ? "NULL" : "?");
    liste_bosalt(&liste);
    return 0;
}

/* Not: sayi satirlarinin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 10 20 30
 * 30 20 10
 * 10 20 30
 * bos liste: NULL
 */
