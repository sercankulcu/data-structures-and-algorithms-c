/* Dinamik dizi: dolunca realloc ile kapasiteyi ikiye katlayan ekle().
 * realloc'un sonucu once gecici t'ye alinir; basarisizlikta eski blok kaybolmaz.
 * Slayt: "ekle() Adim Adim". Ornek nottan (Ornek 2.1): bos diziye
 * 7, 3, 9, 4, 6 eklenir. */
#include <stdio.h>
#include <stdlib.h>

typedef struct { int *veri; int boyut, kap; } DinDizi;

int ekle(DinDizi *d, int x) {
  if (d->boyut == d->kap) {              /* dolu */
    int yeni = d->kap ? 2 * d->kap : 1;
    int *t = realloc(d->veri, yeni * sizeof *t);
    if (t == NULL) return 0;    /* eski blok sağlam */
    d->veri = t;
    d->kap = yeni;
  }
  d->veri[d->boyut++] = x;
  return 1;
}

int main(void) {  /* sunumda yok */
  DinDizi d = {NULL, 0, 0};
  int x[] = {7, 3, 9, 4, 6};
  int i, k;
  for (i = 0; i < 5; i++) {
    if (!ekle(&d, x[i])) {
      printf("bellek yetmedi\n");
      break;
    }
    printf("x = %d: boyut = %d, kap = %d, veri = [", x[i], d.boyut, d.kap);
    for (k = 0; k < d.boyut; k++)
      printf(k ? ", %d" : "%d", d.veri[k]);
    printf("]\n");
  }
  free(d.veri);   /* sunumda yok: diziyi geri ver */
  return 0;
}

/* Beklenen cikti:
 * x = 7: boyut = 1, kap = 1, veri = [7]
 * x = 3: boyut = 2, kap = 2, veri = [7, 3]
 * x = 9: boyut = 3, kap = 4, veri = [7, 3, 9]
 * x = 4: boyut = 4, kap = 4, veri = [7, 3, 9, 4]
 * x = 6: boyut = 5, kap = 8, veri = [7, 3, 9, 4, 6]
 */
