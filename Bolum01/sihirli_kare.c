/* Tek n icin sihirli kare (Coxeter / Siyam kurali): 1 ilk satirin
 * ortasina, her sonraki sayi sol ust caprazina; capraz doluysa bir asagi.
 * Slayt: "Sihirli Kare n = 3". Ornekler nottan: n = 3 ve n = 5. */
#include <stdio.h>
#define MAX 15  /* sunumda yok: dizinin satir uzunlugu */

void sihirli(int n, int k[][MAX]) {
  int i = 0, j = (n - 1) / 2, s, r, c;
  k[i][j] = 1;        /* k sifirlanmis olmali */
  for (s = 2; s <= n * n; s++) {
    r = (i - 1 < 0) ? n - 1 : i - 1; /* yukari */
    c = (j - 1 < 0) ? n - 1 : j - 1; /* sol */
    if (k[r][c]) i = (i + 1) % n; /* in */
    else { i = r; j = c; }
    k[i][j] = s;
  }
}

/* sunumda yok: kareyi ve ilk satirin toplamini yazar */
static void yaz(int n, int k[][MAX]) {
  int i, j, t = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) printf("%3d", k[i][j]);
    printf("\n");
  }
  for (j = 0; j < n; j++) t += k[0][j];
  printf("toplam = %d\n", t);
}

int main(void) {  /* sunumda yok */
  int k3[MAX][MAX] = {{0}};
  int k5[MAX][MAX] = {{0}};
  sihirli(3, k3);
  yaz(3, k3);
  sihirli(5, k5);
  yaz(5, k5);
  return 0;
}

/* Beklenen cikti:
 *   6  1  8
 *   7  5  3
 *   2  9  4
 * toplam = 15
 *  15  8  1 24 17
 *  16 14  7  5 23
 *  22 20 13  6  4
 *   3 21 19 12 10
 *   9  2 25 18 11
 * toplam = 65
 */
