/* Program adimlarini global bir count sayaciyla saymak: sum() 2n + 3,
 * rsum() 2n + 2 adim atar.
 * Slaytlar: "sum() Adim Sayaciyla", "rsum() Cagri Yiginiyla".
 * Ornek nottan: list = {3, 1, 4}, n = 3 (count 9 ve 8). */
#include <stdio.h>

int count = 0;  /* sunumda yok: sayacin bildirimi */

float sum(float list[], int n) {
  float tempsum = 0; count++;
  int i;
  for (i = 0; i < n; i++) {
    count++;             /* for testi */
    tempsum += list[i]; count++;
  }
  count++;  /* for'un son testi */
  count++;  return tempsum;
}

float rsum(float list[], int n) {
  count++;               /* if testi */
  if (n) {
    count++;             /* toplama + return */
    return rsum(list, n - 1) + list[n - 1];
  }
  count++;
  return 0;
}

int main(void) {  /* sunumda yok */
  float list[] = {3, 1, 4};
  float s;
  int n;

  count = 0;
  s = sum(list, 3);
  printf("sum = %.2f, count = %d\n", s, count);

  count = 0;
  s = rsum(list, 3);
  printf("rsum = %.2f, count = %d\n", s, count);

  for (n = 0; n <= 3; n++) {     /* formulleri dogrula */
    count = 0; sum(list, n);
    printf("n = %d: sum %d adim, ", n, count);
    count = 0; rsum(list, n);
    printf("rsum %d adim\n", count);
  }
  return 0;
}

/* Beklenen cikti:
 * sum = 8.00, count = 9
 * rsum = 8.00, count = 8
 * n = 0: sum 3 adim, rsum 2 adim
 * n = 1: sum 5 adim, rsum 4 adim
 * n = 2: sum 7 adim, rsum 6 adim
 * n = 3: sum 9 adim, rsum 8 adim
 */
