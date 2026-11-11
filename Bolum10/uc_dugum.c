/* Kosullu gezinme: uc dugumleri (yapraklari) soldan saga yazma ve yalniz
 * sol cocugu olan dugumleri yazma. Ornek A...L agaci: yapraklar GHJKL,
 * yalniz sol cocuklu dugum F.
 * Slaytlar: "SORU 3-6: Uc Dugumler" (ilk blok), "SORU 7-9". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */

typedef struct agac *agac_gost;
struct agac {
    agac_gost solcocuk;   /* sol alt ağaç */
    char      veri;
    agac_gost sagcocuk;   /* sağ alt ağaç */
};

agac_gost ogeal(void) {          /* yeni düğüm */
    agac_gost p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yok!\n");
        exit(EXIT_FAILURE);
    }
    p->solcocuk = p->sagcocuk = NULL;
    return p;
}

void agac_sil(agac_gost L) {     /* kök sonda */
    if (!L) return;
    agac_sil(L->solcocuk);
    agac_sil(L->sagcocuk);
    free(L);
}

void uc_dugum_yaz(agac_gost L) {
  if (L) {
    uc_dugum_yaz(L->solcocuk);
    if (!L->solcocuk && !L->sagcocuk)
      printf("%c", L->veri);
    uc_dugum_yaz(L->sagcocuk);
  }
}

void yalniz_sol_yaz(agac_gost L) {           /* SORU 7 */
  if (!L) return;
  if (L->solcocuk && !L->sagcocuk)
    printf("%c", L->veri);
  yalniz_sol_yaz(L->solcocuk);
  yalniz_sol_yaz(L->sagcocuk);
}

/* sunumda yok: agac kuran yardimci */
static agac_gost dugum(char veri, agac_gost sol, agac_gost sag)
{
    agac_gost p = ogeal();
    p->veri = veri;
    p->solcocuk = sol;
    p->sagcocuk = sag;
    return p;
}

int main(void)
{
    agac_gost t = dugum('A',
               dugum('B', NULL,
                     dugum('C',
                           dugum('D', dugum('G', NULL, NULL),
                                      dugum('H', NULL, NULL)),
                           dugum('E', NULL,
                                 dugum('I', dugum('J', NULL, NULL),
                                            dugum('K', NULL, NULL))))),
               dugum('F', dugum('L', NULL, NULL), NULL));

    printf("uc_dugum_yaz  : ");
    uc_dugum_yaz(t);
    printf("\nyalniz_sol_yaz: ");
    yalniz_sol_yaz(t);
    printf("\n");
    agac_sil(t);
    return 0;
}

/* Beklenen cikti:
 * uc_dugum_yaz  : GHJKL
 * yalniz_sol_yaz: F
 */
