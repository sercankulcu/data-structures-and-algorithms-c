/* Tek yonlu bagli listenin sonuna ekleme: son dugum p->bag != NULL
 * kosuluyla bulunur. Notlardaki ornek: 4 -> 1 -> 6 listesinin sonuna 5.
 * Slayt: "Sona Ekleme". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

bool sona_ekle(oge_gost *bas, int x) {
    oge_gost p, yeni = malloc(sizeof *yeni);
    if (yeni == NULL) return false;
    yeni->deger = x;
    yeni->bag = NULL;              // yeni son düğüm
    if (*bas == NULL) { *bas = yeni; return true; }
    for (p = *bas; p->bag != NULL; p = p->bag)
        ;                          // son düğümü bul
    p->bag = yeni;
    return true;
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
    oge_gost liste = NULL;
    sona_ekle(&liste, 4);          /* bos liste dali */
    sona_ekle(&liste, 1);
    sona_ekle(&liste, 6);
    yazdir(liste);
    sona_ekle(&liste, 5);
    yazdir(liste);
    liste_bosalt(&liste);
    return 0;
}

/* Not: her satirin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 4 1 6
 * 4 1 6 5
 */
