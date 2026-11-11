/* Ozyinelemeli ikili arama: iki taban durum (aralik bos, bulundu) ve iki
 * kuyruk cagrisi. Slaytlar: "Ozyinelemeli Ikili Arama" ve "... Adim Adim".
 * Test dizisi nottan; 18 ve 25 aranir. */
#include <stdio.h>  /* sunumda yok */

#define COMPARE(x, y) ((x) < (y) ? -1 : (y) < (x) ? 1 : 0)  /* sunumda yok: "Ikili Arama Problemi" slaytindan */

int binsearch(int list[], int x, int l, int r) {
  int m;
  if (l > r) return -1;          /* aralik bos */
  m = (l + r) / 2;
  switch (COMPARE(list[m], x)) {
    case -1: return binsearch(list, x, m + 1, r);
    case 0:  return m;
    case 1:  return binsearch(list, x, l, m - 1);
  }
  return -1;                     /* ulasilmaz */
}

int main(void) {  /* sunumda yok */
  int list[] = {4, 13, 18, 19, 24, 27, 33, 36, 39, 40};
  printf("18 -> %d\n", binsearch(list, 18, 0, 9));
  printf("25 -> %d\n", binsearch(list, 25, 0, 9));
  return 0;
}

/* Beklenen cikti:
 * 18 -> 2
 * 25 -> -1
 */
