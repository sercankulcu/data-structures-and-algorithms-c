/* Iki boyutlu dinamik dizi: once satir isaretcileri, sonra her satir ayri
 * malloc ile ayrilir; bir satir ayrilamazsa oncekiler geri verilir.
 * Slayt: "dizi2b() Adim Adim". Ornek nottan: dizi2b(3, 4), x[i][j] = 10i + j;
 * x[2][3] = 23 ve *(*(x + 1) + 2) = 12. */
#include <stdio.h>
#include <stdlib.h>

int **dizi2b(int satir, int sutun) {
  int i, **x = malloc(satir * sizeof *x);
  if (x == NULL) return NULL;
  for (i = 0; i < satir; i++) {
    x[i] = malloc(sutun * sizeof **x);
    if (x[i] == NULL) {                /* geri al */
      while (--i >= 0) free(x[i]);
      free(x); return NULL;
    }
  }
  return x;
}

/* sunumda yok: once satirlar, sonra isaretci dizisi geri verilir */
static void dizi2b_sil(int **x, int satir) {
  int i;
  for (i = 0; i < satir; i++) free(x[i]);
  free(x);
}

int main(void) {  /* sunumda yok */
  int i, j, **x = dizi2b(3, 4);
  if (x == NULL) {
    printf("Yetersiz bellek\n");
    return 1;
  }
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
      x[i][j] = 10 * i + j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 4; j++) printf("%3d", x[i][j]);
    printf("\n");
  }
  printf("x[2][3] = %d\n", x[2][3]);
  printf("*(*(x + 1) + 2) = %d\n", *(*(x + 1) + 2));
  dizi2b_sil(x, 3);
  return 0;
}

/* Beklenen cikti:
 *   0  1  2  3
 *  10 11 12 13
 *  20 21 22 23
 * x[2][3] = 23
 * *(*(x + 1) + 2) = 12
 */
