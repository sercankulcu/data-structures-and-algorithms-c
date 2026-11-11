/* Ikili agacin bagli gosterimi ve ozyinelemeli gezinmeler: kok onde,
 * kok ortada, kok sonda. Dugumler ogeal ile ayrilir, agac_sil ile birakilir.
 * Son olarak NULL cagrilarini kaldiran (cagirmadan once denetleyen) kok
 * onde surumu ayni ciktiyi verir.
 * Ornek agaclar: A(B(D), C) ve on iki dugumlu A...L agaci
 * (A: sol B, sag F; B: sag C; C: D, E; D: G, H; E: sag I; I: J, K; F: sol L).
 * Slaytlar: "Bagli Gosterim", "Dugum Ayirma", "Ozyinelemeli Gezinme
 * Yordamlari", "kok_ortada_dolas() / kok_onde_dolas() / kok_sonda_dolas()
 * Adim Adim", "Gezinmenin Maliyeti". */
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

void kok_onde_dolas(agac_gost L) {
  if (L) {
    printf("%c", L->veri);
    kok_onde_dolas(L->solcocuk);
    kok_onde_dolas(L->sagcocuk);
  }
}

void kok_ortada_dolas(agac_gost L) {
  if (L) {
    kok_ortada_dolas(L->solcocuk);
    printf("%c", L->veri);
    kok_ortada_dolas(L->sagcocuk);
  }
}

void kok_sonda_dolas(agac_gost L) {
  if (L) {
    kok_sonda_dolas(L->solcocuk);
    kok_sonda_dolas(L->sagcocuk);
    printf("%c", L->veri);
  }
}

/* "Gezinmenin Maliyeti": iki cagri satiri "sonra" bicimiyle yazilmis kok
 * onde gezinme (sunumda yok: fonksiyonun adi ve cercevesi).
 *   once : kok_onde_dolas(L->solcocuk); kok_onde_dolas(L->sagcocuk);
 *          (n+1 NULL cagrisi) */
void kok_onde_dolas_denetimli(agac_gost L) {
  if (L) {
    printf("%c", L->veri);
    /* sonra: çağırmadan denetle */
    if (L->solcocuk) kok_onde_dolas_denetimli(L->solcocuk);
    if (L->sagcocuk) kok_onde_dolas_denetimli(L->sagcocuk);
  }
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

static void uc_gezinme(const char *ad, agac_gost t)
{
    printf("%s\n  kok onde  : ", ad);
    kok_onde_dolas(t);
    printf("\n  kok ortada: ");
    kok_ortada_dolas(t);
    printf("\n  kok sonda : ");
    kok_sonda_dolas(t);
    printf("\n");
}

int main(void)
{
    agac_gost t1, t2;

    /* A(B(D), C) */
    t1 = dugum('A', dugum('B', dugum('D', NULL, NULL), NULL),
                    dugum('C', NULL, NULL));
    /* A...L agaci */
    t2 = dugum('A',
               dugum('B', NULL,
                     dugum('C',
                           dugum('D', dugum('G', NULL, NULL),
                                      dugum('H', NULL, NULL)),
                           dugum('E', NULL,
                                 dugum('I', dugum('J', NULL, NULL),
                                            dugum('K', NULL, NULL))))),
               dugum('F', dugum('L', NULL, NULL), NULL));

    uc_gezinme("A(B(D),C)", t1);
    uc_gezinme("A...L", t2);
    printf("denetimli kok onde (A...L): ");
    kok_onde_dolas_denetimli(t2);
    printf("\n");

    agac_sil(t1);
    agac_sil(t2);
    return 0;
}

/* Beklenen cikti:
 * A(B(D),C)
 *   kok onde  : ABDC
 *   kok ortada: DBAC
 *   kok sonda : DBCA
 * A...L
 *   kok onde  : ABCDGHEIJKFL
 *   kok ortada: BGDHCEJIKALF
 *   kok sonda : GHDJKIECBLFA
 * denetimli kok onde (A...L): ABCDGHEIJKFL
 */
