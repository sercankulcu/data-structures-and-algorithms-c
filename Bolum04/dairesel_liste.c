/* Dairesel bagli liste: liste son isaretcisiyle tutulur, ilk dugum
 * son->bag'dir. d_uzunluk do-while ile turu sayar; d_basa_ekle O(1)'de
 * basa ekler, ardindan *son = yeni yazilirsa ayni dugum sona eklenmis olur.
 * Notlardaki ornek: 3 -> 5 -> 8 halkasi.
 * Slaytlar: "Dairesel Liste", "Dairesel: Ekleme". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

int d_uzunluk(oge_gost son) {
    int n = 0;
    oge_gost p = son;
    if (son == NULL) return 0;   // boş liste
    do {
        n++;
        p = p->bag;
    } while (p != son);          // tur tamamlandı
    return n;
}

void d_basa_ekle(oge_gost *son, oge_gost yeni) {
    if (*son == NULL) {           // boş liste
        *son = yeni;
        yeni->bag = yeni;        // kendini gösterir
    } else {
        yeni->bag = (*son)->bag;  // eski ilk düğüm
        (*son)->bag = yeni;
    }
}

/* sunumda yok: dugum ayirir */
static oge_gost yeni_oge(int x) {
    oge_gost p = malloc(sizeof *p);
    if (p == NULL) exit(1);
    p->deger = x;
    p->bag = NULL;
    return p;
}

/* sunumda yok: ilk dugumden (son->bag) baslayip bir tur yazar */
static void d_yazdir(oge_gost son) {
    oge_gost p;
    if (son != NULL) {
        p = son->bag;
        do {
            printf("%d ", p->deger);
            p = p->bag;
        } while (p != son->bag);
    }
    printf("(uzunluk %d)\n", d_uzunluk(son));
}

/* sunumda yok: halkayi acip butun dugumleri iade eder */
static void d_bosalt(oge_gost *son) {
    oge_gost p, q;
    if (*son == NULL) return;
    p = (*son)->bag;
    (*son)->bag = NULL;
    while (p != NULL) {
        q = p->bag;
        free(p);
        p = q;
    }
    *son = NULL;
}

int main(void)
{
    oge_gost son = NULL;
    oge_gost yeni;
    d_yazdir(son);
    d_basa_ekle(&son, yeni_oge(8));   /* bos liste: kendini gosterir */
    d_basa_ekle(&son, yeni_oge(5));
    d_basa_ekle(&son, yeni_oge(3));
    d_yazdir(son);
    d_basa_ekle(&son, yeni_oge(1));   /* basa ekleme */
    d_yazdir(son);
    yeni = yeni_oge(9);               /* sona ekleme */
    d_basa_ekle(&son, yeni);
    son = yeni;
    d_yazdir(son);
    d_bosalt(&son);
    return 0;
}

/* Beklenen cikti:
 * (uzunluk 0)
 * 3 5 8 (uzunluk 3)
 * 1 3 5 8 (uzunluk 4)
 * 1 3 5 8 9 (uzunluk 5)
 */
