/* Baslik dugumlu listede sirali ekleme: onceki baslikta baslar ve asla
 * NULL olmaz, bu yuzden basa/araya/sona/bos listeye ekleme ayni iki
 * satirdir. Notlardaki ornek: bos baslikli listeye 8, 3, 5, 1, 9.
 * Slayt: "Baslik Dugumu". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

// başlıklı listede sıralı ekleme: özel durum yok
void b_sirali_ekle(oge_gost baslik, oge_gost yeni) {
    oge_gost onceki = baslik;       // asla NULL değil
    while (onceki->bag != NULL &&
           onceki->bag->deger < yeni->deger)
        onceki = onceki->bag;
    yeni->bag = onceki->bag;
    onceki->bag = yeni;
}

/* sunumda yok: dugum ayirir */
static oge_gost yeni_oge(int x) {
    oge_gost p = malloc(sizeof *p);
    if (p == NULL) exit(1);
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

int main(void)
{
    struct oge H = {0, NULL};               /* sunumda yok: baslik dugumu; deger kullanilmaz */
    int girdi[] = {8, 3, 5, 1, 9};
    oge_gost p, q;
    for (int i = 0; i < 5; i++) {
        b_sirali_ekle(&H, yeni_oge(girdi[i]));
        printf("%d eklendi: ", girdi[i]);
        yazdir(H.bag);                      /* gercek dugumler basliktan sonra */
    }
    for (p = H.bag; p != NULL; p = q) {     /* sunumda yok: bosaltma */
        q = p->bag;
        free(p);
    }
    return 0;
}

/* Not: her satirin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * 8 eklendi: 8
 * 3 eklendi: 3 8
 * 5 eklendi: 3 5 8
 * 1 eklendi: 1 3 5 8
 * 9 eklendi: 1 3 5 8 9
 */
