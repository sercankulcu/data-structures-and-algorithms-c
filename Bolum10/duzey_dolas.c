/* Duzey duzey (level-order) gezinme: dairesel dizi kuyruguna dugum
 * adresleri konur; kuyruktan alinan dugum yazilir, var olan cocuklari
 * arkaya eklenir. Ornekler: A...H agaci, A...L agaci ve bos agac.
 * Slaytlar: "Duzey Duzey: Kuyruk", "duzey_dolas() Adim Adim". */
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

void kuyruk_ekle(int on, int *arka,
                 agac_gost p, agac_gost k[]) {
  *arka = (*arka + 1) % MAX_SIZE;
  if (*arka == on) {            /* dolu */
    fprintf(stderr, "Kuyruk dolu\n");
    exit(EXIT_FAILURE);
  }
  k[*arka] = p;
}
agac_gost kuyruk_al(int *on, int arka,
                    agac_gost k[]) {
  if (*on == arka) return NULL; /* boş */
  *on = (*on + 1) % MAX_SIZE;
  return k[*on];
}

void duzey_dolas(agac_gost L) {
  agac_gost kuyruk[MAX_SIZE];
  int on = 0, arka = 0;
  if (!L) return;              // ağaç boş olabilir
  kuyruk_ekle(on, &arka, L, kuyruk);
  while ((L = kuyruk_al(&on, arka, kuyruk))) {
    printf("%c", L->veri);
    if (L->solcocuk)
      kuyruk_ekle(on, &arka, L->solcocuk, kuyruk);
    if (L->sagcocuk)
      kuyruk_ekle(on, &arka, L->sagcocuk, kuyruk);
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
    /* A...H: A(B(D(H), E), C(F, G)) */
    agac_gost t1 = dugum('A',
                         dugum('B', dugum('D', dugum('H', NULL, NULL), NULL),
                                    dugum('E', NULL, NULL)),
                         dugum('C', dugum('F', NULL, NULL), dugum('G', NULL, NULL)));
    /* A...L agaci */
    agac_gost t2 = dugum('A',
               dugum('B', NULL,
                     dugum('C',
                           dugum('D', dugum('G', NULL, NULL),
                                      dugum('H', NULL, NULL)),
                           dugum('E', NULL,
                                 dugum('I', dugum('J', NULL, NULL),
                                            dugum('K', NULL, NULL))))),
               dugum('F', dugum('L', NULL, NULL), NULL));

    printf("A...H   : [");
    duzey_dolas(t1);
    printf("]\nA...L   : [");
    duzey_dolas(t2);
    printf("]\nbos agac: [");
    duzey_dolas(NULL);
    printf("]\n");
    agac_sil(t1);
    agac_sil(t2);
    return 0;
}

/* Beklenen cikti:
 * A...H   : [ABCDEFGH]
 * A...L   : [ABFCLDEGHIJK]
 * bos agac: []
 */
