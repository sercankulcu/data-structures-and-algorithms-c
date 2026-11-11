/* Takasla permutasyon uretimi: i. konuma sirayla her kalan oge getirilir,
 * alt cagridan sonra takas geri alinir. Slaytlar: "perm("abc") Adim Adim"
 * ve devami. */
#include <stdio.h>  /* sunumda yok */

#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))  /* sunumda yok: Bolum 1'deki makro */

void perm(char *list, int i, int n) {
  int j, temp;
  if (i == n) {                  /* bir dizilis */
    for (j = 0; j < n; j++) printf("%c", list[j]);
    printf("\n");
  } else
    for (j = i; j < n; j++) {
      SWAP(list[i], list[j], temp);
      perm(list, i + 1, n);
      SWAP(list[i], list[j], temp);
    }
}

int main(void) {  /* sunumda yok */
  char list[] = "abc";           /* degistirilebilir dizi olmali */
  perm(list, 0, 3);
  printf("son durum: %s\n", list);
  return 0;
}

/* Beklenen cikti:
 * abc
 * acb
 * bac
 * bca
 * cba
 * cab
 * son durum: abc
 */
