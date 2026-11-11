/* Satir oncelikli duzende iki boyutlu dizinin bayt adresi:
 * alfa + (i * ust1 + j) * s. Slayt: "adres() Adim Adim".
 * int x[3][4], alfa = 100, s = 4: x[1][2] -> 124, x[2][3] -> 144. */
#include <stdio.h>  /* sunumda yok */

/* int x[3][4]: satır öncelikli bayt adresi */
long adres(long alfa, int i, int j,
           int ust1, int s) {
  long k = (long)i * ust1 + j;   /* öncekiler */
  return alfa + k * s;
}

int main(void) {
  printf("%ld\n", adres(100, 1, 2, 4, 4));
  printf("%ld\n", adres(100, 2, 3, 4, 4));
  return 0;
}

/* Beklenen cikti:
 * 124
 * 144
 */
