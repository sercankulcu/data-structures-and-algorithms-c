/* Kesir ADT'sini yalniz arayuzunden kullanan program: 1/2 + 1/3 = 5/6.
 * Slayt: "Arayuzu Kullanmak". Sona nottaki 2/4 = 1/2 esitlik ornegi eklendi. */
/* main.c : yalnizca arayuzu bilir */
#include "kesir.h"
#include <stddef.h> /* NULL */
#include <stdio.h>  /* sunumda yok: printf icin */
int main(void) {
  Kesir *a = kesir_olustur(1, 2);
  Kesir *b = kesir_olustur(1, 3);
  Kesir *t = NULL;
  if (a && b) t = kesir_topla(a, b);
  if (t) kesir_yaz(t);  /* 5/6 */
  kesir_sil(a); kesir_sil(b);
  kesir_sil(t);  /* free(NULL) zararsiz */

  /* sunumda yok: kesir_esit denemesi (nottaki 2/4 ile 1/2 ornegi) */
  {
    Kesir *c = kesir_olustur(2, 4);
    Kesir *d = kesir_olustur(1, 2);
    if (c && d) printf("2/4 == 1/2 ? %d\n", kesir_esit(c, d));
    kesir_sil(c); kesir_sil(d);
  }
  return 0;
}

/* Beklenen cikti:
 * 5/6
 * 2/4 == 1/2 ? 1
 */
