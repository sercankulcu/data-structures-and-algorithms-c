/* Agac yordamlari: agac_kopyala (yeni dugumlerden ayni agac), esitmi ve
 * esitmi2 (ayni sekil ve ayni veriler), cocukdegistir (SWAP makrosuyla
 * aynadaki goruntu). Ornekler: A...L agacinin kopyasi, A(B,C) ile A(B,D)
 * karsilastirmasi, A(B(D),C)'de cocuklarin iki kez degistirilmesi.
 * Slaytlar: "Agac Kopyalama", "agac_kopyala() Adim Adim", "Es Bicimlilik",
 * "esitmi() Adim Adim", "esitmi Farkli Yazim", "cocukdegistir() Adim Adim". */
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

/* "Ozyinelemeli Gezinme Yordamlari" slaytindan, ciktilar icin */
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

agac_gost agac_kopyala(agac_gost L) {
  if (!L) return NULL;
  agac_gost T = malloc(sizeof *T);
  if (!T) { perror("malloc"); exit(1); }
  T->solcocuk = agac_kopyala(L->solcocuk);
  T->sagcocuk = agac_kopyala(L->sagcocuk);
  T->veri = L->veri;
  return T;
}

int esitmi(agac_gost L, agac_gost T) {
  return (!L && !T) ||
         (L && T && L->veri == T->veri
          && esitmi(L->solcocuk, T->solcocuk)
          && esitmi(L->sagcocuk, T->sagcocuk));
}

int esitmi2(agac_gost L, agac_gost T) {
  if (L == NULL || T == NULL)
    return L == T;          /* ikisi de NULL mı? */
  if (L->veri != T->veri)
    return 0;
  if (!esitmi2(L->solcocuk, T->solcocuk))
    return 0;
  return esitmi2(L->sagcocuk, T->sagcocuk);
}

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void cocukdegistir(agac_gost L) {
  agac_gost p;
  if (L) {
    SWAP(L->solcocuk, L->sagcocuk, p);
    cocukdegistir(L->solcocuk);
    cocukdegistir(L->sagcocuk);
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

int main(void)
{
    agac_gost t, k, L, T, m, m2;

    /* A...L agaci ve kopyasi */
    t = dugum('A',
               dugum('B', NULL,
                     dugum('C',
                           dugum('D', dugum('G', NULL, NULL),
                                      dugum('H', NULL, NULL)),
                           dugum('E', NULL,
                                 dugum('I', dugum('J', NULL, NULL),
                                            dugum('K', NULL, NULL))))),
               dugum('F', dugum('L', NULL, NULL), NULL));
    k = agac_kopyala(t);
    printf("kopya kok onde  : ");
    kok_onde_dolas(k);
    printf("\nkopya kok ortada: ");
    kok_ortada_dolas(k);
    printf("\nesitmi(t, kopya) = %d, esitmi2 = %d, ayni kok mu: %d\n",
           esitmi(t, k), esitmi2(t, k), t == k);

    /* A(B, C) ile A(B, D) */
    L = dugum('A', dugum('B', NULL, NULL), dugum('C', NULL, NULL));
    T = dugum('A', dugum('B', NULL, NULL), dugum('D', NULL, NULL));
    printf("esitmi(A(B,C), A(B,D)) = %d, esitmi2 = %d\n",
           esitmi(L, T), esitmi2(L, T));

    /* A(B(D), C): cocukdegistir */
    m = dugum('A', dugum('B', dugum('D', NULL, NULL), NULL), dugum('C', NULL, NULL));
    m2 = agac_kopyala(m);
    printf("kok ortada: ");
    kok_ortada_dolas(m);
    cocukdegistir(m);
    printf("\ncocukdegistir sonrasi: ");
    kok_ortada_dolas(m);
    printf(", esitmi(m, ilk hali) = %d\n", esitmi(m, m2));
    cocukdegistir(m);
    printf("ikinci kez: ");
    kok_ortada_dolas(m);
    printf(", esitmi(m, ilk hali) = %d\n", esitmi(m, m2));

    agac_sil(t);
    agac_sil(k);
    agac_sil(L);
    agac_sil(T);
    agac_sil(m);
    agac_sil(m2);
    return 0;
}

/* Beklenen cikti:
 * kopya kok onde  : ABCDGHEIJKFL
 * kopya kok ortada: BGDHCEJIKALF
 * esitmi(t, kopya) = 1, esitmi2 = 1, ayni kok mu: 0
 * esitmi(A(B,C), A(B,D)) = 0, esitmi2 = 0
 * kok ortada: DBAC
 * cocukdegistir sonrasi: CABD, esitmi(m, ilk hali) = 0
 * ikinci kez: DBAC, esitmi(m, ilk hali) = 1
 */
