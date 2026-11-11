/* malloc ve denetimini yeni_oge'de toplamak; onceki dugumun pesine ekleme
 * (sonrasina_ekle). Liste 12 -> 7 -> 25 bu fonksiyonla kurulur, sonra
 * notlardaki ornekteki gibi 7'nin arkasina 9 eklenir: 12 -> 7 -> 9 -> 25.
 * Slaytlar: "malloc ve free", "Araya Ekleme". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

oge_gost yeni_oge(int x) {
    oge_gost p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yetmiyor yetmiyoor...\n");
        exit(1);
    }
    p->deger = x;
    p->bag = NULL;
    return p;
}

// onceki'nin peşine x değerli yeni düğüm ekler
oge_gost sonrasina_ekle(oge_gost onceki, int x) {
    oge_gost p = yeni_oge(x);  // malloc + denetim
    if (onceki != NULL) {      // araya ya da sona
        p->bag = onceki->bag;
        onceki->bag = p;
    }                          // yoksa tek başına
    return p;
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
    oge_gost liste = sonrasina_ekle(NULL, 12);   /* tek basina: yeni liste */
    oge_gost yedi = sonrasina_ekle(liste, 7);    /* sona */
    sonrasina_ekle(yedi, 25);                    /* sona */
    yazdir(liste);
    sonrasina_ekle(yedi, 9);                     /* araya */
    yazdir(liste);
    liste_bosalt(&liste);
    return 0;
}

/* Not: her satirin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 12 7 25
 * 12 7 9 25
 */
