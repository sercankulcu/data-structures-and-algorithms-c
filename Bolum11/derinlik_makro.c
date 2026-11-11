/* Tek satirlik derinlik ve makro tuzagi: MAX bir makro oldugu icin
 * buyuk cikan alt agac cagrisi iki kez isletilir. Sonuc dogrudur ama cagri
 * sayisi zincirde 3 * 2^n - 2'ye cikar (yerel degiskenli surum 2n + 1
 * cagri yapar). Notlardaki olcum: 4 ve 12 dugumluk zincirler; bir de 7
 * dugumluk dolu agac.
 * Slayt: "Derinlik Profesyonelce". */
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))  /* sunumda yok: notta verilen makro */

typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};

static long cagri = 0;   /* sunumda yok: cagri sayaci */

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

int derinlik(agac_gost L) {    /* tek satır */
  cagri++;                     /* sunumda yok: sayac */
  return !L ? 0 : MAX(derinlik(L->solcocuk),
                      derinlik(L->sagcocuk)) + 1;
}

/* sunumda yok: agaci bellege iade eder (kok sonda) */
static void agac_sil(agac_gost L) {
    if (L) {
        agac_sil(L->solcocuk);
        agac_sil(L->sagcocuk);
        free(L);
    }
}

/* sunumda yok: derinligi ve cagri sayisini yazar */
static void olc(const char *ad, int n, agac_gost L) {
    cagri = 0;
    int d = derinlik(L);
    printf("%s (n = %d): derinlik = %d, cagri = %ld, 2n + 1 = %d\n",
           ad, n, d, cagri, 2 * n + 1);
}

int main(void)
{
    agac_gost z4 = NULL, z12 = NULL, dolu = NULL;
    for (int i = 1; i <= 4; i++) z4 = ekle(z4, i);      /* saga zincir */
    for (int i = 1; i <= 12; i++) z12 = ekle(z12, i);
    int sira[] = {4, 2, 6, 1, 3, 5, 7};                 /* 3 duzey dolu */
    for (int i = 0; i < 7; i++) dolu = ekle(dolu, sira[i]);

    olc("zincir", 4, z4);
    olc("zincir", 12, z12);
    olc("dolu agac", 7, dolu);

    agac_sil(z4);
    agac_sil(z12);
    agac_sil(dolu);
    return 0;
}

/* Beklenen cikti:
 * zincir (n = 4): derinlik = 4, cagri = 46, 2n + 1 = 9
 * zincir (n = 12): derinlik = 12, cagri = 12286, 2n + 1 = 25
 * dolu agac (n = 7): derinlik = 3, cagri = 40, 2n + 1 = 15
 */
