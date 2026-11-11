/* Sinav sorusu: ayni problemi cozmeye calisan kotu AgirlikBul kac kez
 * cagrilir? Her alt agaci iki kez cagirdigi icin zincirde Theta(2^n),
 * dengeli agacta Theta(n^2) surer; ustelik kosullarin icindeki cagrilarin
 * sonucu kullanilmadigi icin x kokte degilse hep 0 dondurur. Program bu
 * yanlis sonucu da gosterir; kodda tanimsiz davranis yoktur.
 * Notlardaki ornek: kok 2, cocuklari 10 ve 20 olan agacta x = 20 icin 14,
 * x = 30 icin 21 cagri; 4 dugumluk zincirde x yokken 61 cagri.
 * Slayt: "Sinav: Cagri Sayisi". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi ("Ekleme Nasil Yapilir" slaytindaki) */
typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};
typedef agac_gost oge_gost;   /* sunumda yok: sorudaki tip adi */

static long cagri = 0;        /* sunumda yok: cagri sayaci */

/* sunumda yok: agirlik(L) = L'nin kok oldugu alt agacin derinligi */
static int agirlik(oge_gost L) {
    if (!L) return 0;
    int sol = agirlik(L->solcocuk), sag = agirlik(L->sagcocuk);
    return (sol > sag ? sol : sag) + 1;
}

int AgirlikBul(oge_gost L, int x) {
  cagri++;                    /* sunumda yok: sayac */
  if (!L) return 0;
  else if (L->veri == x) return agirlik(L);
  if (AgirlikBul(L->solcocuk, x) >
      AgirlikBul(L->sagcocuk, x))
    AgirlikBul(L->solcocuk, x);
  if (AgirlikBul(L->sagcocuk, x) >
      AgirlikBul(L->solcocuk, x))
    AgirlikBul(L->sagcocuk, x);
  return 0;
}

/* sunumda yok: tek dugum ayirir */
static agac_gost dugum_yap(int x) {
    agac_gost r = malloc(sizeof *r);
    if (!r) {
        fprintf(stderr, "Bellek yetersiz\n");
        exit(EXIT_FAILURE);
    }
    r->veri = x;
    r->solcocuk = r->sagcocuk = NULL;
    return r;
}

/* sunumda yok: agaci bellege iade eder (kok sonda) */
static void agac_sil(agac_gost L) {
    if (L) {
        agac_sil(L->solcocuk);
        agac_sil(L->sagcocuk);
        free(L);
    }
}

/* sunumda yok: sonucu ve cagri sayisini yazar */
static void olc(const char *ad, oge_gost L, int x) {
    cagri = 0;
    int a = AgirlikBul(L, x);
    printf("%s, x = %d: donen = %d, cagri = %ld\n", ad, x, a, cagri);
}

int main(void)
{
    /* 2(10, 20) */
    agac_gost K = dugum_yap(2);
    K->solcocuk = dugum_yap(10);
    K->sagcocuk = dugum_yap(20);
    olc("2(10, 20)", K, 2);
    olc("2(10, 20)", K, 20);   /* dogru cevap 1 */
    olc("2(10, 20)", K, 30);

    /* saga zincir 1 -> 2 -> 3 -> 4 */
    agac_gost Z = dugum_yap(1), p = Z;
    for (int i = 2; i <= 4; i++) {
        p->sagcocuk = dugum_yap(i);
        p = p->sagcocuk;
    }
    olc("4 dugumluk zincir", Z, 99);

    agac_sil(K);
    agac_sil(Z);
    return 0;
}

/* Beklenen cikti:
 * 2(10, 20), x = 2: donen = 2, cagri = 1
 * 2(10, 20), x = 20: donen = 0, cagri = 14
 * 2(10, 20), x = 30: donen = 0, cagri = 21
 * 4 dugumluk zincir, x = 99: donen = 0, cagri = 61
 */
