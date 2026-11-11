/* Sinav sorusu: x'i iceren ogenin agirligi = o ogenin kok oldugu alt
 * agacin derinligi. Cozum iki bilinen yordamin bilesimidir:
 * derinlik(agacta_ara(L, x)). Yordam icinde yerel prototipler bildirilir;
 * derinlik makro degil max fonksiyonu kullanir.
 * Notlardaki ornekler: kok 2, cocuklari 10 ve 20 olan agacta 2, 10, 20, 30
 * (2, 1, 1, 0); silme ornegi agacinda 40, 60, 50, 56 (6, 5, 4, 1).
 * Slayt: "Sinav: Agirlik Bul". */
#include <stdio.h>
#include <stdlib.h>

typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};

int AgirlikBul(agac_gost L, int x) {
  /* agacta_ara: x'i içeren öğe ya da NULL */
  agac_gost agacta_ara(agac_gost L, int x);
  int derinlik(agac_gost L);
  return derinlik(agacta_ara(L, x));
}
agac_gost agacta_ara(agac_gost L, int x) {
  if (!L) return NULL;
  if (L->veri == x) return L;
  agac_gost T = agacta_ara(L->solcocuk, x);
  return T ? T : agacta_ara(L->sagcocuk, x);
}
int derinlik(agac_gost L) {
  int max(int a, int b);  /* a,b'den küçük olmayan */
  return L ? max(derinlik(L->solcocuk),
                 derinlik(L->sagcocuk)) + 1 : 0;
}

/* sunumda yok: max fonksiyonu (ders notundan) */
int max(int a, int b) { return a > b ? a : b; }

/* sunumda yok: ogeal'in govdesi (ders notundaki gerceklemesi) */
agac_gost ogeal(void) {
    agac_gost r = malloc(sizeof *r);
    if (!r) {
        fprintf(stderr, "Bellek yetersiz\n");
        exit(EXIT_FAILURE);
    }
    r->solcocuk = r->sagcocuk = NULL;
    return r;
}

/* sunumda yok: agaci kurmak icin "Neden agac_gost *L" slaytindaki ekle */
agac_gost ekle(agac_gost L, int x) {
  if (!L) {
    L = ogeal();
    L->veri = x;
  } else if (x < L->veri)
    L->solcocuk = ekle(L->solcocuk, x);
  else if (x > L->veri)
    L->sagcocuk = ekle(L->sagcocuk, x);
  return L;        /* kok = ekle(kok, x); */
}

/* sunumda yok: agaci bellege iade eder (kok sonda) */
static void agac_sil(agac_gost L) {
    if (L) {
        agac_sil(L->solcocuk);
        agac_sil(L->sagcocuk);
        free(L);
    }
}

int main(void)
{
    /* arama agaci olmayan agac: 2(10, 20) */
    agac_gost K = ogeal();
    K->veri = 2;
    K->solcocuk = ogeal();
    K->solcocuk->veri = 10;
    K->sagcocuk = ogeal();
    K->sagcocuk->veri = 20;
    int x1[] = {2, 10, 20, 30};
    for (int i = 0; i < 4; i++)
        printf("AgirlikBul(K, %d) = %d\n", x1[i], AgirlikBul(K, x1[i]));

    int sira[] = {40, 20, 60, 10, 30, 50, 70, 42, 55, 65, 73, 52, 57, 66, 56};
    agac_gost L = NULL;
    for (int i = 0; i < 15; i++)
        L = ekle(L, sira[i]);
    int x2[] = {40, 60, 50, 56};
    for (int i = 0; i < 4; i++)
        printf("AgirlikBul(L, %d) = %d\n", x2[i], AgirlikBul(L, x2[i]));
    printf("AgirlikBul(NULL, 5) = %d\n", AgirlikBul(NULL, 5));

    agac_sil(K);
    agac_sil(L);
    return 0;
}

/* Beklenen cikti:
 * AgirlikBul(K, 2) = 2
 * AgirlikBul(K, 10) = 1
 * AgirlikBul(K, 20) = 1
 * AgirlikBul(K, 30) = 0
 * AgirlikBul(L, 40) = 6
 * AgirlikBul(L, 60) = 5
 * AgirlikBul(L, 50) = 4
 * AgirlikBul(L, 56) = 1
 * AgirlikBul(NULL, 5) = 0
 */
