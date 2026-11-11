/* Morris gezinmesi: bayraksiz siradan ikili agacta yiginsiz kok ortada
 * gezinme. Sola inmeden once oncule gecici bir kilavuz kurulur, ikinci
 * geliste sokulur; gezinme bitince agac eski haline doner.
 * Notlardaki ornek (Tablo 12.9): A(B(D, E), C), cikti DBEAC.
 * Slayt: "Morris Gezinmesi". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: Bolum 11'deki dugum tipi */
typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};

void morris_kokortada(agac_gost L) {
  while (L) {
    if (!L->solcocuk) {             /* sol yok: yaz, sağa */
      printf("%c", L->veri);  L = L->sagcocuk;
    } else {
      agac_gost p = L->solcocuk;    /* kök ortada öncülü */
      while (p->sagcocuk && p->sagcocuk != L)
        p = p->sagcocuk;
      if (!p->sagcocuk) {           /* geçici kılavuz kur */
        p->sagcocuk = L;  L = L->solcocuk;
      } else {                      /* kılavuzu sök */
        p->sagcocuk = NULL;
        printf("%c", L->veri);  L = L->sagcocuk;
      }
    }
  }
}

/* sunumda yok: karsilastirma icin ozyinelemeli kok ortada (ders notundan) */
void kokortada(agac_gost p) {
  if (p) {
    kokortada(p->solcocuk);
    printf("%c", p->veri);
    kokortada(p->sagcocuk);
  }
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

int main(void)
{
    /* A(B(D, E), C) */
    agac_gost A = dugum_yap('A');
    A->solcocuk = dugum_yap('B');
    A->sagcocuk = dugum_yap('C');
    A->solcocuk->solcocuk = dugum_yap('D');
    A->solcocuk->sagcocuk = dugum_yap('E');
    agac_gost D = A->solcocuk->solcocuk, E = A->solcocuk->sagcocuk;

    printf("morris:       ");
    morris_kokortada(A);
    printf("\nozyinelemeli: ");
    kokortada(A);
    printf("\nD ve E'nin sagi yine NULL: %s\n",
           (D->sagcocuk == NULL && E->sagcocuk == NULL) ? "evet" : "hayir");

    agac_sil(A);
    return 0;
}

/* Beklenen cikti:
 * morris:       DBEAC
 * ozyinelemeli: DBEAC
 * D ve E'nin sagi yine NULL: evet
 */
