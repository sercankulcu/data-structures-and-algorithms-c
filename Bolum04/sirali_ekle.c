/* Sirali bagli listeye ekleme: onceki ve p birlikte ilerler, yeni dugum
 * ikisinin arasina girer; onceki NULL kalirsa bas degisir.
 * Notlardaki ornek: 2 -> 5 -> 9 listesine 7, sonra 1 (basa), 10 (sona)
 * ve var olan 5 (eskisinin onune).
 * Slayt: "Sirali Ekleme Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

void sirali_ekle(oge_gost *bas, oge_gost yeni) {
    oge_gost onceki = NULL, p = *bas;
    while (p != NULL && p->deger < yeni->deger) {
        onceki = p;
        p = p->bag;
    }
    yeni->bag = p;
    if (onceki == NULL) *bas = yeni;  // başa
    else onceki->bag = yeni;          // araya/sona
}

/* sunumda yok: dugumu ayirip degerini yazar ("malloc ve free" slaytindaki yeni_oge) */
static oge_gost yeni_oge(int x) {
    oge_gost p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yetmiyor\n");
        exit(1);
    }
    p->deger = x;
    p->bag = NULL;
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
    oge_gost liste = NULL;
    oge_gost bes;
    sirali_ekle(&liste, yeni_oge(2));
    sirali_ekle(&liste, yeni_oge(5));
    sirali_ekle(&liste, yeni_oge(9));
    yazdir(liste);
    sirali_ekle(&liste, yeni_oge(7));    /* araya */
    yazdir(liste);
    sirali_ekle(&liste, yeni_oge(1));    /* basa */
    yazdir(liste);
    sirali_ekle(&liste, yeni_oge(10));   /* sona */
    yazdir(liste);
    bes = yeni_oge(5);                   /* esit deger */
    sirali_ekle(&liste, bes);
    yazdir(liste);
    printf("yeni 5 eskisinin onunde: %s\n",
           bes->bag != NULL && bes->bag->deger == 5 ? "evet" : "hayir");
    liste_bosalt(&liste);
    return 0;
}

/* Not: sayi satirlarinin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 2 5 9
 * 2 5 7 9
 * 1 2 5 7 9
 * 1 2 5 7 9 10
 * 1 2 5 5 7 9 10
 * yeni 5 eskisinin onunde: evet
 */
