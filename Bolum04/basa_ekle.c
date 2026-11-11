/* Tek yonlu bagli listede gezinme (yazdir) ve basa ekleme (basa_ekle).
 * Bos listeye 2, sonra 7 eklenir (7 -> 2); notlardaki izlemedeki gibi
 * ardindan 5 eklenir (5 -> 7 -> 2).
 * Slaytlar: "Dugum Yapisi", "Gezinme", "Basa Ekleme", "Basa Ekleme Adim Adim". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct oge *oge_gost;  // önce işaretçi türü

struct oge {
    int deger;       // veri alanı
    oge_gost bag;    // sonraki düğümün adresi
};

void yazdir(oge_gost p) {
    for (; p != NULL; p = p->bag)
        printf("%d ", p->deger);
    printf("\n");
}

bool basa_ekle(oge_gost *bas, int x) {
    oge_gost yeni = malloc(sizeof *yeni);
    if (yeni == NULL) return false;  // bellek yok
    yeni->deger = x;
    yeni->bag = *bas;    // önce eski başı koru
    *bas = yeni;         // sonra başı değiştir
    return true;
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
    oge_gost liste = NULL;  // boş liste
    basa_ekle(&liste, 2);   // 2
    yazdir(liste);
    basa_ekle(&liste, 7);   // 7 -> 2
    yazdir(liste);
    basa_ekle(&liste, 5);   /* sunumda yok: notlardaki izleme, 5 -> 7 -> 2 */
    yazdir(liste);
    liste_bosalt(&liste);   /* sunumda yok */
    return 0;
}

/* Not: her satirin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 2
 * 7 2
 * 5 7 2
 */
