/* && islecinin soldan saga ve kisa devre degerlendirilmesi: i < n yanlissa
 * a[i] hic okunmaz; iki bicim aynidir. Slayt: "&& Degerlendirme Sirasi". */
#include <stdio.h>

int main(void) {  /* sunumda yok */
  int a[] = {5, 0, 7};
  int n = 3, i;
  for (i = 0; i <= n; i++) {        /* i = n'de a[n] okunmamali */
    /* 1 */ if (i < n && a[i] != 0) printf("1: a[%d] = %d\n", i, a[i]);

    /* 2 */ if (i < n)
              if (a[i] != 0) printf("2: a[%d] = %d\n", i, a[i]);
  }
  printf("a[%d] hic okunmadi\n", n);
  return 0;
}

/* Beklenen cikti:
 * 1: a[0] = 5
 * 2: a[0] = 5
 * 1: a[2] = 7
 * 2: a[2] = 7
 * a[3] hic okunmadi
 */
