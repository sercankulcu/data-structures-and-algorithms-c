/* Diziyi fonksiyona gecirmek: dizi adi ilk ogenin adresine donusur;
 * yazdir() her ogenin adresini ve degerini isaretci aritmetigiyle yazar.
 * Slayt: "yazdir() Adim Adim". */
#include <stdio.h>

void yazdir(int *p, int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%p %d\n", (void *)(p + i), *(p + i));
}

int main(void) {
  int dizi[] = {10, 20, 30, 40};
  yazdir(dizi, 4);
  return 0;
}

/* Adresler her calistirmada degisir; asagidaki blok bir ornek calistirmadir
 * ve birebir tutmasi beklenmez. Degismeyen: ardisik iki adres arasindaki fark
 * sizeof(int) = 4 bayttir ve degerler 10, 20, 30, 40'tir. */
/* Beklenen cikti:
 * 000000AA18BFFBB0 10
 * 000000AA18BFFBB4 20
 * 000000AA18BFFBB8 30
 * 000000AA18BFFBBC 40
 */
