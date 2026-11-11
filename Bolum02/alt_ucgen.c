/* Alt ucgen matrisi tek boyutlu ALT dizisinde satir satir saklamak:
 * a[i][j] (j <= i) -> k = i(i + 1)/2 + j. Hata kodlari: -1 ust ucgen,
 * -2 gecersiz indis. Slaytlar: "AltUcgenOku() Adim Adim",
 * "AltUcgenEris() Adim Adim". Ornek nottan (Ornek 2.2): n = 4, girdi
 * 3 1 4 1 5 9 2 6 5 3. */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: scanf yerine sabit girdi (stdin bos) */
static const int girdi[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
static int okunan = 0;
static void oku(int *p) { *p = girdi[okunan++]; }

#define MAX_SIZE 100
void AltUcgenOku(int alt[], int n) {
  int i, j, k;
  if (n * (n + 1) / 2 > MAX_SIZE) {
    printf("Alt dizi boyutu yetersiz!\n"); exit(1);
  }
  for (i = 0; i < n; i++) {
    k = (i + 1) * i / 2;      /* öncekiler */
    for (j = 0; j <= i; j++)  /* j <= i */
      oku(&alt[k + j]);       /* sunumda: scanf("%d", &alt[k + j]); */
  }
}

int AltUcgenEris(int i, int j, int n) {
  if (i < 0 || i >= n || j < 0 || j >= n) {
    printf("Gecersiz indis\n");
    return -2;
  } else if (i < j) return -1;    /* üst üçgen: 0 */
  else return (i + 1) * i / 2 + j;   /* geçerli */
}

int main(void) {  /* sunumda yok (son uc printf slayttaki main'den) */
  int alt[MAX_SIZE], k;
  AltUcgenOku(alt, 4);
  printf("alt:");
  for (k = 0; k < 10; k++) printf(" %d", alt[k]);
  printf("\n");

  printf("%d\n", AltUcgenEris(2, 1, 4));
  printf("%d\n", AltUcgenEris(1, 3, 4));
  printf("%d\n", AltUcgenEris(4, 0, 4));
  return 0;
}

/* Beklenen cikti:
 * alt: 3 1 4 1 5 9 2 6 5 3
 * 4
 * -1
 * Gecersiz indis
 * -2
 */
