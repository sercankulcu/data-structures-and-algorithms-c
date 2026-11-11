/* Ikili arama agacindan silme: bag (isaretcinin isaretcisi) p'ye giden
 * bagi tutar; iki cocuklu dugumde sol alt agacin en buyugu yukari tasinir.
 * Notlardaki ornek: 40, 20, 60, 10, 30, 50, 70, 42, 55, 65, 73, 52, 57,
 * 66, 56 agacindan 60 silinir (57 yukari cikar, 56 55'in sagina gecer,
 * derinlik 6'dan 5'e iner). Sonra agacta olmayan 99 silinmek istenir ve en
 * sonda butun degerler silinerek agac bosaltilir.
 * Slayt: "sil() Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))  /* sunumda yok: notta verilen makro */

typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};

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

/* sunumda yok: "derinlik() Adim Adim" slaytindaki derinlik */
int derinlik(agac_gost L) {
  int sol, sag;
  if (L) {                   // işaretçi NULL mı
    sol = derinlik(L->solcocuk);
    sag = derinlik(L->sagcocuk);
    return MAX(sol, sag) + 1;
  }
  else return 0;             // uç yaprağa ulaşıldı
}

void sil(int x, agac_gost *L) {
  agac_gost p = *L, *bag = L;  // bag: p'ye giden
  while (p && p->veri != x) {  // x'i ara
    bag = (x < p->veri) ? &p->solcocuk
                        : &p->sagcocuk;
    p = *bag;
  }
  if (!p) return;              // x yok
  if (p->solcocuk && p->sagcocuk) {  // 2 çocuk
    agac_gost *b = &p->solcocuk;     // sol alt
    while ((*b)->sagcocuk)           // ağacın en
      b = &(*b)->sagcocuk;           // büyüğü
    p->veri = (*b)->veri;      // veriyi taşı
    bag = b;  p = *b;          // onu sileceğiz
  }
  *bag = p->solcocuk ? p->solcocuk : p->sagcocuk;
  free(p);
}

/* sunumda yok: kok ortada gezinme */
static void kokortada(agac_gost L) {
    if (L) {
        kokortada(L->solcocuk);
        printf(" %d", L->veri);
        kokortada(L->sagcocuk);
    }
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

/* sunumda yok: agacin durumunu yazar */
static void durum(agac_gost L) {
    printf("agac: ");
    yaz(L);
    printf("\nkok ortada:");
    kokortada(L);
    printf("\nderinlik: %d\n", derinlik(L));
}

int main(void)
{
    int sira[] = {40, 20, 60, 10, 30, 50, 70, 42, 55, 65, 73, 52, 57, 66, 56};
    agac_gost L = NULL;
    for (int i = 0; i < 15; i++)
        L = ekle(L, sira[i]);
    durum(L);

    printf("-- sil(60)\n");
    sil(60, &L);
    durum(L);

    printf("-- sil(99)\n");
    sil(99, &L);           /* yok: agac degismez */
    printf("derinlik: %d\n", derinlik(L));

    for (int i = 0; i < 15; i++)
        sil(sira[i], &L);  /* 60 artik yok; o cagri bir sey yapmaz */
    printf("hepsi silindi, L %s\n", L == NULL ? "NULL" : "NULL degil");
    return 0;
}

/* Beklenen cikti:
 * agac: 40(20(10, 30), 60(50(42, 55(52, 57(56, -))), 70(65(-, 66), 73)))
 * kok ortada: 10 20 30 40 42 50 52 55 56 57 60 65 66 70 73
 * derinlik: 6
 * -- sil(60)
 * agac: 40(20(10, 30), 57(50(42, 55(52, 56)), 70(65(-, 66), 73)))
 * kok ortada: 10 20 30 40 42 50 52 55 56 57 65 66 70 73
 * derinlik: 5
 * -- sil(99)
 * derinlik: 5
 * hepsi silindi, L NULL
 */
