/* Yiginla (ozyinelemesiz) gezinme: kok ortada, kok onde (iki cozum), kok
 * sonda ve kok ortada gezinmede yalniz uc dugumleri yazma. Yigina
 * dugumlerin adresleri konur; yigit_al bos yiginda NULL dondurur.
 * Ornek agaclar: A(B(D,E),C) ve A...L agaci.
 * Slaytlar: "Yinelemeli Kok Ortada Kodu", "Yinelemeli Kok Ortada Adim Adim",
 * "SORU 1 Cozumu", "Yinelemeli Kok Sonda Adim Adim", "SORU 3-6: Uc Dugumler"
 * (ikinci blok: yiginli surumdeki kosul). */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */

#define MAX_SIZE 100  /* sunumda yok */

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

void yigit_ekle(int *ust, agac_gost p,
                agac_gost y[]) {
  if (*ust == MAX_SIZE - 1) {
    fprintf(stderr, "Yigit dolu\n");
    exit(EXIT_FAILURE);
  }
  y[++*ust] = p;
}
agac_gost yigit_al(int *ust,
                    agac_gost y[]) {
  return (*ust == -1) ? NULL : y[(*ust)--];
}

void kok_ortada_dolas(agac_gost L) {
  agac_gost yigit[MAX_SIZE];
  int ust = -1;
  for (;;) {
    for (; L; L = L->solcocuk)  // solları at
      yigit_ekle(&ust, L, yigit);
    L = yigit_al(&ust, yigit);  // boşsa NULL
    if (!L) break;
    printf("%c", L->veri);
    L = L->sagcocuk;
  }
}

void kok_onde_dolas_d(agac_gost L) {
  agac_gost yigit[MAX_SIZE];
  int ust = -1;
  for (;;) {
    for (; L; L = L->solcocuk) {
      printf("%c", L->veri);   // girerken yaz
      yigit_ekle(&ust, L, yigit);
    }
    L = yigit_al(&ust, yigit);
    if (!L) break;
    L = L->sagcocuk;
  }
}

/* SORU 1'in ikinci cozumu: slayttaki parca bu fonksiyonun govdesidir
 * (sunumda yok: fonksiyon adi ve yigin bildirimi). */
void kok_onde_dolas_d2(agac_gost L) {
  agac_gost yigit[MAX_SIZE];
  int ust = -1;
if (L) yigit_ekle(&ust, L, yigit);
while ((L = yigit_al(&ust, yigit))) {
  printf("%c", L->veri);
  if (L->sagcocuk)
    yigit_ekle(&ust, L->sagcocuk, yigit);
  if (L->solcocuk)
    yigit_ekle(&ust, L->solcocuk, yigit);
}
}

void kok_sonda_dolas_d(agac_gost L) {
  agac_gost yigit[MAX_SIZE], son = NULL, t;
  int ust = -1;
  while (L || ust != -1) {
    if (L) {                     // sola in
      yigit_ekle(&ust, L, yigit);
      L = L->solcocuk;
    } else {
      t = yigit[ust];            // tepeye bak
      if (t->sagcocuk && t->sagcocuk != son)
        L = t->sagcocuk;         // önce sağ
      else {
        printf("%c", t->veri);
        son = yigit_al(&ust, yigit);
      }
    }
  }
}

/* SORU 5: yiginli kok ortada gezinmede printf satiri slayttaki kosula
 * baglanir (sunumda yok: fonksiyon adi). */
void uc_dugum_yaz_d(agac_gost L) {
  agac_gost yigit[MAX_SIZE];
  int ust = -1;
  for (;;) {
    for (; L; L = L->solcocuk)
      yigit_ekle(&ust, L, yigit);
    L = yigit_al(&ust, yigit);
    if (!L) break;
    if (!L->solcocuk && !L->sagcocuk)
      printf("%c", L->veri);
    L = L->sagcocuk;
  }
}

/* sunumda yok: agac kuran yardimci ve deneme */
static agac_gost dugum(char veri, agac_gost sol, agac_gost sag)
{
    agac_gost p = ogeal();
    p->veri = veri;
    p->solcocuk = sol;
    p->sagcocuk = sag;
    return p;
}

static void dene(const char *ad, agac_gost t)
{
    printf("%s\n  kok ortada : ", ad);
    kok_ortada_dolas(t);
    printf("\n  kok onde   : ");
    kok_onde_dolas_d(t);
    printf("\n  kok onde 2 : ");
    kok_onde_dolas_d2(t);
    printf("\n  kok sonda  : ");
    kok_sonda_dolas_d(t);
    printf("\n  uc dugumler: ");
    uc_dugum_yaz_d(t);
    printf("\n");
}

int main(void)
{
    agac_gost t1, t2;

    /* A(B(D, E), C) */
    t1 = dugum('A', dugum('B', dugum('D', NULL, NULL), dugum('E', NULL, NULL)),
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

    dene("A(B(D,E),C)", t1);
    dene("A...L", t2);
    agac_sil(t1);
    agac_sil(t2);
    return 0;
}

/* Beklenen cikti:
 * A(B(D,E),C)
 *   kok ortada : DBEAC
 *   kok onde   : ABDEC
 *   kok onde 2 : ABDEC
 *   kok sonda  : DEBCA
 *   uc dugumler: DEC
 * A...L
 *   kok ortada : BGDHCEJIKALF
 *   kok onde   : ABCDGHEIJKFL
 *   kok onde 2 : ABCDGHEIJKFL
 *   kok sonda  : GHDJKIECBLFA
 *   uc dugumler: GHJKL
 */
