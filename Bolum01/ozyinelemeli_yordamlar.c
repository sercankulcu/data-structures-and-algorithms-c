/* Ozyinelemeli yordamlar: faktoriyel, Fibonacci ve binom katsayisi
 * (Pascal ucgeni bagintisi). Slayt: "Odev Cevaplari".
 * Ornekler nottan: fakt(5), fakt(10), fibo(10), komb(5, 2), komb(10, 3). */
#include <stdio.h>

long fakt(long n) {
  if (n <= 1) return 1;
  return n * fakt(n - 1);
}

long fibo(long n) {
  if (n <= 1) return n;   /* f0 = 0, f1 = 1 */
  return fibo(n - 1) + fibo(n - 2);
}

long komb(int n, int m) {
  if (m == 0 || m == n) return 1;
  return komb(n - 1, m) + komb(n - 1, m - 1);
}

int main(void) {  /* sunumda yok */
  printf("fakt(5) = %ld\n", fakt(5));
  printf("fakt(10) = %ld\n", fakt(10));
  printf("fibo(10) = %ld\n", fibo(10));
  printf("komb(5, 2) = %ld\n", komb(5, 2));
  printf("komb(10, 3) = %ld\n", komb(10, 3));
  return 0;
}

/* Beklenen cikti:
 * fakt(5) = 120
 * fakt(10) = 3628800
 * fibo(10) = 55
 * komb(5, 2) = 10
 * komb(10, 3) = 120
 */
