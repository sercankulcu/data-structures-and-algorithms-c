/* Ikili arama agacina ekleme: yinelemeli arama_agacina_ekle (q arka,
 * p on isaretci, kok adresle gelir) ve yeni koku donduren ozyinelemeli
 * ekle. Notlardaki ornek: 47, 55, 49, 26, 34, 17, 52, 84, 93 iki yordamla
 * ayri ayri eklenir; sonra 50 (eklenir) ve 47 (zaten var) denenir.
 * Slaytlar: "Ekleme Nasil Yapilir", "arama_agacina_ekle() Adim Adim",
 * "Neden agac_gost *L". */
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } boolean;
typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};
/* ogeal(): malloc + NULL denetimi,
   çocukları NULL yapar */

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

boolean arama_agacina_ekle(int x, agac_gost *L) {
  agac_gost q = NULL, p = *L, r; // q arka, p ön
  while (p) {                    // NULL'a dek in
    q = p;                       // arkayı günle
    if (x < p->veri) p = p->solcocuk;
    else if (x > p->veri) p = p->sagcocuk;
    else { printf("Benzer deger var.\n");
           return FALSE; }
  }
  r = ogeal();                   // çocuklar NULL
  r->veri = x;
  if (*L == NULL) *L = r;        // boş ağaç: kök
  else if (x < q->veri) q->solcocuk = r;
  else q->sagcocuk = r;
  return TRUE;
}

/* Özyinelemeli alternatif: yeni kökü döndürür */
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

/* sunumda yok: kok onde gezinme (her degerden once bir bosluk) */
static void kokonde(agac_gost L) {
    if (L) {
        printf(" %d", L->veri);
        kokonde(L->solcocuk);
        kokonde(L->sagcocuk);
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
    int sira[] = {47, 55, 49, 26, 34, 17, 52, 84, 93};
    agac_gost L = NULL;     /* arama_agacina_ekle ile */
    agac_gost kok = NULL;   /* ekle ile */
    for (int i = 0; i < 9; i++) {
        arama_agacina_ekle(sira[i], &L);
        kok = ekle(kok, sira[i]);
    }
    printf("kok onde (yinelemeli):");
    kokonde(L);
    printf("\nkok onde (ozyinelemeli):");
    kokonde(kok);
    printf("\nkok ortada:");
    kokortada(L);
    printf("\n");

    int s = (int) arama_agacina_ekle(50, &L);
    printf("arama_agacina_ekle(50) = %d\n", s);
    s = (int) arama_agacina_ekle(47, &L);
    printf("arama_agacina_ekle(47) = %d\n", s);
    printf("kok onde:");
    kokonde(L);
    printf("\n");

    kok = ekle(kok, 47);    /* esit deger sessizce reddedilir */
    printf("ekle(kok, 47) sonrasi kok onde:");
    kokonde(kok);
    printf("\n");

    agac_sil(L);
    agac_sil(kok);
    return 0;
}

/* Beklenen cikti:
 * kok onde (yinelemeli): 47 26 17 34 55 49 52 84 93
 * kok onde (ozyinelemeli): 47 26 17 34 55 49 52 84 93
 * kok ortada: 17 26 34 47 49 52 55 84 93
 * arama_agacina_ekle(50) = 1
 * Benzer deger var.
 * arama_agacina_ekle(47) = 0
 * kok onde: 47 26 17 34 55 49 52 50 84 93
 * ekle(kok, 47) sonrasi kok onde: 47 26 17 34 55 49 52 84 93
 */
