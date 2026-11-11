/* Faktoriyelin uc bicimi: ozyinelemeli, dongulu ve birikimli parametreyle
 * kuyruk ozyinelemeli. Slaytlar: "Ozyineleme ve Dongu", "Kuyruk
 * Ozyinelemesi". Ornek nottan: fakt_k(4, 1) -> 24. */
#include <stdio.h>  /* sunumda yok */

/* ozyinelemeli */
long fakt(int n) {
  return n <= 1 ? 1 : n * fakt(n - 1);
}

/* dongulu */
long fakt_d(int n) {
  long f = 1;
  while (n > 1)
    f *= n--;
  return f;
}

long fakt_k(int n, long acc) {
  if (n <= 1) return acc;
  return fakt_k(n - 1, n * acc);  /* son is: cagri */
}
/* ilk cagri: fakt_k(n, 1) */

int main(void) {  /* sunumda yok */
  int ornek[] = {0, 1, 4, 10};
  int k;
  for (k = 0; k < 4; k++) {
    int n = ornek[k];
    printf("n = %d: fakt %ld, fakt_d %ld, fakt_k %ld\n",
           n, fakt(n), fakt_d(n), fakt_k(n, 1));
  }
  return 0;
}

/* Beklenen cikti:
 * n = 0: fakt 1, fakt_d 1, fakt_k 1
 * n = 1: fakt 1, fakt_d 1, fakt_k 1
 * n = 4: fakt 24, fakt_d 24, fakt_k 24
 * n = 10: fakt 3628800, fakt_d 3628800, fakt_k 3628800
 */
