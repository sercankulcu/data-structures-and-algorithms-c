/* Tek boyutlu dizi bildirimi, adres formulu (alfa + i * sizeof(int)) ve
 * sizeof. Slayt: "C'de Tek Boyutlu Dizi". Degerler 64 bit Linux icindir
 * (sizeof(int) = 4). */
#include <stdio.h>

int main(void) {  /* sunumda yok */
  int list[5], *plist[5];
  /* list : 5 tamsayı       */
  /* plist: 5 tamsayı işaretçisi */
  int i;

  for (i = 0; i < 5; i++) {     /* sunumda yok: dizileri doldur */
    list[i] = 10 * (i + 1);
    plist[i] = &list[i];
  }

  i = 3;
  /* list[i]  -- adresi: alfa + i * sizeof(int) */
  printf("list[%d] = %d\n", i, list[i]);
  printf("&list[%d] - &list[0] = %td oge = %td bayt\n", i,
         &list[i] - &list[0],
         (char *)&list[i] - (char *)&list[0]);
  /* sizeof list  -- 5 * sizeof(int) bayt */
  printf("sizeof list = %zu, 5 * sizeof(int) = %zu\n",
         sizeof list, 5 * sizeof(int));
  printf("*plist[2] = %d\n", *plist[2]);
  return 0;
}

/* Beklenen cikti:
 * list[3] = 40
 * &list[3] - &list[0] = 3 oge = 12 bayt
 * sizeof list = 20, 5 * sizeof(int) = 20
 * *plist[2] = 30
 */
