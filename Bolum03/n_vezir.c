/* n-vezir problemi geri izlemeyle: q[r] r. satirdaki vezirin sutunu;
 * uygun() ayni sutun ve capraz cakismasini sinar, yerlestir() satir satir
 * dener ve cikmazda geri doner. Slaytlar: "n-Vezir Problemi",
 * "4-Vezir Adim Adim". Ornekler nottan: n = 4 ve n = 8 icin ilk cozum. */
#include <stdio.h>
#include <stdlib.h>  /* sunumda yok: abs */

int q[8];  /* q[r]: r. satirdaki vezirin sutunu */

int uygun(int r, int c) {
  int i;
  for (i = 0; i < r; i++)
    if (q[i] == c || abs(q[i] - c) == r - i)
      return 0;         /* ayni sutun ya da capraz */
  return 1;
}

int yerlestir(int r, int n) {
  int c;
  if (r == n) return 1;             /* cozum */
  for (c = 0; c < n; c++)
    if (uygun(r, c)) {
      q[r] = c;
      if (yerlestir(r + 1, n)) return 1;
    }
  return 0;                  /* geri don */
}

/* sunumda yok: cozumu dizi ve tahta olarak yazar */
static void yaz(int n) {
  int r, c;
  printf("q =");
  for (r = 0; r < n; r++) printf(" %d", q[r]);
  printf("\n");
  for (r = 0; r < n; r++) {
    for (c = 0; c < n; c++) printf("%c", q[r] == c ? 'V' : '.');
    printf("\n");
  }
}

int main(void) {  /* sunumda yok */
  if (yerlestir(0, 4)) yaz(4);
  if (yerlestir(0, 8)) yaz(8);
  return 0;
}

/* Beklenen cikti:
 * q = 1 3 0 2
 * .V..
 * ...V
 * V...
 * ..V.
 * q = 0 4 7 5 2 6 1 3
 * V.......
 * ....V...
 * .......V
 * .....V..
 * ..V.....
 * ......V.
 * .V......
 * ...V....
 */
