/* yigit.c: opak yiginin gerceklemesi. Dizi yapinin icinde sabit degildir;
 * yigit_olustur istenen kapasiteyle heap'ten ayirir.
 * Slayt: "Arayuz ve Gercekleme" (2. blok). yigit_ekle, yigit_al ve
 * yigit_bos slaytta yok; struct surumundeki push/pop gibi yazildi. */
#include <stdlib.h>   /* sunumda yok */
#include "yigit.h"    /* sunumda yok */

/* yigit.c: gerçekleme */
struct Yigit { int *veri; int ust, kap; };

Yigit *yigit_olustur(int kap) {
  Yigit *y = malloc(sizeof *y);
  if (y == NULL) return NULL;
  y->veri = malloc(kap * sizeof *y->veri);
  if (y->veri == NULL) {
    free(y);  return NULL;
  }
  y->ust = -1;  y->kap = kap;
  return y;
}
void yigit_yok_et(Yigit *y) {
  if (y) { free(y->veri); free(y); }
}

/* sunumda yok */
bool yigit_ekle(Yigit *y, int x) {
  if (y->ust == y->kap - 1) return false;   /* tasma */
  y->veri[++y->ust] = x;
  return true;
}

/* sunumda yok */
bool yigit_al(Yigit *y, int *x) {
  if (y->ust < 0) return false;             /* alt tasma */
  *x = y->veri[y->ust--];
  return true;
}

/* sunumda yok */
bool yigit_bos(const Yigit *y) { return y->ust < 0; }
