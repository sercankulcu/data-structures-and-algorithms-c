/* Bagli listede degere gore arama (ara) ve 0 tabanli konuma gore erisim
 * (konum). Notlardaki ornek: 4 -> 1 -> 6 -> 5 listesinde konum 0, 3, 4.
 * Slayt: "Arama ve Konum". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

oge_gost ara(oge_gost p, int x) {
    while (p != NULL && p->deger != x)
        p = p->bag;
    return p;               // bulunamazsa NULL
}

oge_gost konum(oge_gost p, int i) {  // 0 tabanlı
    while (p != NULL && i-- > 0)
        p = p->bag;
    return p;               // i >= uzunluk ise NULL
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

/* sunumda yok: bulunan dugumu ya da NULL'i yazar */
static void goster(const char *ne, oge_gost p) {
    if (p == NULL) printf("%s -> NULL\n", ne);
    else printf("%s -> %d\n", ne, p->deger);
}

int main(void)
{
    int a[] = {4, 1, 6, 5};
    oge_gost liste = liste_kur(a, 4);
    goster("ara(liste, 6)", ara(liste, 6));
    goster("ara(liste, 42)", ara(liste, 42));
    goster("konum(liste, 0)", konum(liste, 0));
    goster("konum(liste, 3)", konum(liste, 3));
    goster("konum(liste, 4)", konum(liste, 4));
    liste_bosalt(&liste);
    return 0;
}

/* Beklenen cikti:
 * ara(liste, 6) -> 6
 * ara(liste, 42) -> NULL
 * konum(liste, 0) -> 4
 * konum(liste, 3) -> 5
 * konum(liste, 4) -> NULL
 */
