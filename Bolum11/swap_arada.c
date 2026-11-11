/* Sinav sorusu: SWAP iki ozyinelemeli cagrinin arasinda. Yordam sol alt
 * agaci isler, cocuklari degistirir, sonra yeni sag cocugu (yani az once
 * islenmis eski solu) yeniden isler. Sonuc ayna degildir: yalniz kokun iki
 * alt agaci yer degistirir.
 * Notlardaki ornek: 44, 30, 15, 18, 86, 97, 65, 113, 74, 129 ile kurulan
 * ikili arama agaci.
 * Slayt: "Sinav: SWAP Arada". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: notta verilen SWAP makrosu */
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};

void yordam(agac_gost L) {
  agac_gost p;
  if (L) {
    yordam(L->solcocuk);
    SWAP(L->solcocuk, L->sagcocuk, p);
    yordam(L->sagcocuk);
  }
}

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

/* sunumda yok: agaci kok(sol, sag) biciminde yazar, bos alt agac "-" */
static void yaz(agac_gost L) {
    if (!L) { printf("-"); return; }
    printf("%d", L->veri);
    if (L->solcocuk || L->sagcocuk) {
        printf("(");
        yaz(L->solcocuk);
        printf(", ");
        yaz(L->sagcocuk);
        printf(")");
    }
}

/* sunumda yok: kok ortada gezinme */
static void kokortada(agac_gost L) {
    if (L) {
        kokortada(L->solcocuk);
        printf(" %d", L->veri);
        kokortada(L->sagcocuk);
    }
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
    int sira[] = {44, 30, 15, 18, 86, 97, 65, 113, 74, 129};
    agac_gost L = NULL;
    for (int i = 0; i < 10; i++)
        L = ekle(L, sira[i]);
    printf("once:  ");
    yaz(L);
    printf("\n");
    yordam(L);
    printf("sonra: ");
    yaz(L);
    printf("\nkok ortada:");
    kokortada(L);
    printf("\n");
    agac_sil(L);
    return 0;
}

/* Beklenen cikti:
 * once:  44(30(15(-, 18), -), 86(65(-, 74), 97(-, 113(-, 129))))
 * sonra: 44(86(65(-, 74), 97(-, 113(-, 129))), 30(15(-, 18), -))
 * kok ortada: 65 74 86 97 113 129 44 15 18 30
 */
