/* Ilk ozyineleme ornegi: taban durum n <= 1, adim n * fakt(n - 1).
 * Slayt: "fakt(3) Adim Adim". */
#include <stdio.h>  /* sunumda yok */

long fakt(int n) {
  if (n <= 1)
    return 1;              /* taban durum */
  return n * fakt(n - 1);
}

int main(void) {
  printf("%ld\n", fakt(3));
  return 0;
}

/* Beklenen cikti:
 * 6
 */
