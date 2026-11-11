/* N x N matris carpimi: c[i][j] = toplam a[i][k] * b[k][j], N^3 carpma.
 * Slayt: "mult() Adim Adim". Ornek nottan: A = [[1, 2], [3, 4]],
 * B = [[5, 6], [7, 8]] -> C = [[19, 22], [43, 50]]. */
#include <stdio.h>  /* sunumda yok */

#define N 2
void mult(int a[][N], int b[][N], int c[][N]) {
  int i, j, k;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++) {
      c[i][j] = 0;
      for (k = 0; k < N; k++)
        c[i][j] += a[i][k] * b[k][j];
    }
}

int main(void) {  /* sunumda yok */
  int a[N][N] = {{1, 2}, {3, 4}};
  int b[N][N] = {{5, 6}, {7, 8}};
  int c[N][N];
  int i, j;
  mult(a, b, c);
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) printf("%4d", c[i][j]);
    printf("\n");
  }
  return 0;
}

/* Beklenen cikti:
 *   19  22
 *   43  50
 */
