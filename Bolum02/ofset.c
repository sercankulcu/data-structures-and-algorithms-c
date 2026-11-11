/* n boyutlu dizide ogenin bagil konumu, Horner yontemiyle:
 * t = (...((i0 * u1 + i1) * u2 + i2) ...). Slayt: "ofset() Adim Adim".
 * Ornek nottan: G[2][2][3] dizisinde G[1][0][2] -> 8. */
#include <stdio.h>  /* sunumda yok */

/* ind: indisler, ust: boyutlar, n: boyut sayısı */
int ofset(const int ind[], const int ust[], int n) {
  int j, t = ind[0];
  for (j = 1; j < n; j++)
    t = t * ust[j] + ind[j];            /* Horner */
  return t;               /* adres = alfa + t*s */
}

int main(void) {  /* sunumda yok */
  int G[2][2][3];
  int ind[] = {1, 0, 2}, ust[] = {2, 2, 3};
  printf("ofset = %d\n", ofset(ind, ust, 3));
  /* gercek dizide ayni konum: bayt farki / sizeof(int) */
  printf("&G[1][0][2] - &G[0][0][0] = %d\n",
         (int)(((char *)&G[1][0][2] - (char *)G) / (int)sizeof(int)));
  return 0;
}

/* Beklenen cikti:
 * ofset = 8
 * &G[1][0][2] - &G[0][0][0] = 8
 */
