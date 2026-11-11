/* Degere gore silme: onceki ile p birlikte ilerler; bastaki dugum
 * silinirse *bas degisir. Notlardaki ornek: 3 -> 8 -> 1 -> 6 listesinden
 * once 1, sonra bastaki 3 silinir, en sonda listede olmayan 42 aranir.
 * Slayt: "Silme Adim Adim". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

bool sil(oge_gost *bas, int x) {
    oge_gost onceki = NULL, p = *bas;
    while (p != NULL && p->deger != x) {
        onceki = p;
        p = p->bag;
    }
    if (p == NULL) return false;        // x yok
    if (onceki == NULL) *bas = p->bag;  // baştaki
    else onceki->bag = p->bag;          // atla
    free(p);
    return true;
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
    int a[] = {3, 8, 1, 6};
    int silinecek[] = {1, 3, 42};
    oge_gost liste = liste_kur(a, 4);
    yazdir(liste);
    for (int i = 0; i < 3; i++) {
        bool sonuc = sil(&liste, silinecek[i]);
        printf("sil(%d) = %s: ", silinecek[i], sonuc ? "true" : "false");
        yazdir(liste);
    }
    liste_bosalt(&liste);
    return 0;
}

/* Not: her satirin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 3 8 1 6
 * sil(1) = true: 3 8 6
 * sil(3) = true: 8 6
 * sil(42) = false: 8 6
 */
