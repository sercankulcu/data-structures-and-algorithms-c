/* strlen'in yaptigi is: isaretci '\0'a kadar ilerletilir, uzunluk
 * isaretci farkidir. Slayt: "uzunluk() Adim Adim". Ornek: uzunluk("veri"). */
#include <stdio.h>
#include <stddef.h>  /* sunumda yok: size_t */

size_t uzunluk(const char *s) {
  const char *p = s;
  while (*p != '\0')     /* sonlandırıcıya dek */
    p++;
  return (size_t)(p - s);  /* işaretçi farkı */
}

int main(void) {  /* sunumda yok */
  printf("%zu\n", uzunluk("veri"));
  printf("%zu\n", uzunluk(""));
  return 0;
}

/* Beklenen cikti:
 * 4
 * 0
 */
