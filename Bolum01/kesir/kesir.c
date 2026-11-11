/* Kesir ADT'sinin gerceklemesi: struct kesir yalniz bu dosyada tanimli.
 * Slaytlar: "C'de Soyutlama: Baslik Dosyasi" (kesir_olustur) ve
 * "Arayuzu Kullanmak" (kesir_topla, kesir_esit, kesir_yaz, kesir_sil). */
/* kesir.c : gercekleme (NASIL?) */
#include <stdio.h>
#include <stdlib.h>
#include "kesir.h"

struct kesir { int pay, payda; };

Kesir *kesir_olustur(int pay, int payda) {
  Kesir *k;
  if (payda == 0) return NULL;
  k = malloc(sizeof *k);
  if (k == NULL) return NULL;
  k->pay = pay;
  k->payda = payda;
  return k;
}

Kesir *kesir_topla(const Kesir *a,
                   const Kesir *b) {
  return kesir_olustur(
      a->pay * b->payda
        + b->pay * a->payda,
      a->payda * b->payda);
}
int kesir_esit(const Kesir *a,
               const Kesir *b) {
  return a->pay * b->payda
      == b->pay * a->payda;
}
void kesir_yaz(const Kesir *k) {
  printf("%d/%d\n", k->pay, k->payda);
}
void kesir_sil(Kesir *k) { free(k); }
