/* Takasin iki bicimi: SWAP makrosu ve isaretci alan swap() fonksiyonu.
 * Slaytlar: "SWAP: Makro ve Fonksiyon" (iki blok), "swap() Adim Adim".
 * Ornek: a = 3, b = 8 (slayt) ve secimli siralamanin ilk turundaki takas
 * (list[0] ile list[1], nottaki {29, 10, 14, 37, 13} dizisi). */
#include <stdio.h>

#define SWAP(x, y, t) \
        ((t) = (x), (x) = (y), (y) = (t))

void swap(int *x, int *y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

/* sunumda yok: diziyi yazan yardimci */
static void dizi_yaz(const int list[], int n) {
  int k;
  for (k = 0; k < n; k++) printf("%d ", list[k]);
  printf("\n");
}

int main(void) {
  int a = 3, b = 8;
  int list[] = {29, 10, 14, 37, 13};  /* sunumda yok: ornek dizi */
  int i = 0, min = 1;                 /* sunumda yok: ilk turun indisleri */
  swap(&a, &b);
  printf("%d %d\n", a, b);

  {
    int temp;
    SWAP(list[i], list[min], temp);
  }
  dizi_yaz(list, 5);              /* sunumda yok */

  swap(&list[i], &list[min]);     /* ayni takas fonksiyonla: geri alir */
  dizi_yaz(list, 5);              /* sunumda yok */
  return 0;                       /* sunumda yok */
}

/* Makronun tuzagi (notta anlatilir, burada calistirilmaz):
 * SWAP(a[i++], a[j], t) yazilirsa i++ iki kez islenir ve takas bozulur. */

/* Beklenen cikti:
 * 8 3
 * 10 29 14 37 13
 * 29 10 14 37 13
 */
