/* Butun listeyi bellege iade etmek: ozyinelemeli serbest_birak (once basi
 * ilerlet, sonra eski basi birak, ayni adresle devam) ve dongulu
 * liste_bosalt. Iki surum de cagirandaki liste degiskenini NULL yapar.
 * Notlardaki ornek: 4 -> 9.
 * Slaytlar: "Sinav Sorusu: serbest_birak" (iki surum), "Serbest Birakma
 * Adim Adim", "Yinelemeli Bosaltma". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

/* Sinav sorusundaki iki surum list_gost *list alir (list_gost == oge_gost).
 * Soldaki surum hatalidir ve calistirilmaz:
 *
 *   void serbest_birak( list_gost *list ){
 *       oge_gost p = *list;
 *       if( *list ){
 *           p = *list->bag;      // derlenmez: *(list->bag) diye okunur
 *           free(*list);
 *           serbest_birak(&p);   // yerel p'nin adresi: cagirandaki liste
 *   }}                           // degismez, sarkan isaretci olarak kalir
 *
 * Sagdaki dogru surum:
 *
 *   void serbest_birak( list_gost *list ){
 *       oge_gost p = *list;
 *       if( p ){
 *           *list = p->bag;
 *           free(p);
 *           serbest_birak(list);
 *   }}
 *
 * Asagidaki "Adim Adim" surumu bununla aynidir. */
void serbest_birak(oge_gost *list) {
    oge_gost p = *list;
    if (p) {
        *list = p->bag;      // önce başı ilerlet
        free(p);             // sonra eski başı bırak
        serbest_birak(list); // aynı adresle devam
    }
}

void liste_bosalt(oge_gost *list) {
    while (*list != NULL) {
        oge_gost p = *list;
        *list = p->bag;     // önce ilerle
        free(p);            // sonra bırak
    }
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

int main(void)
{
    int a[] = {4, 9};
    int b[] = {10, 20, 30};
    oge_gost liste = liste_kur(a, 2);
    yazdir(liste);
    serbest_birak(&liste);
    printf("serbest_birak sonrasi liste %s NULL\n", liste == NULL ? "==" : "!=");

    liste = liste_kur(b, 3);
    yazdir(liste);
    liste_bosalt(&liste);
    printf("liste_bosalt sonrasi liste %s NULL\n", liste == NULL ? "==" : "!=");
    return 0;
}

/* Not: sayi satirlarinin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 4 9
 * serbest_birak sonrasi liste == NULL
 * 10 20 30
 * liste_bosalt sonrasi liste == NULL
 */
