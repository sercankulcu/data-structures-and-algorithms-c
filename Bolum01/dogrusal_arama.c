/* Bekcili dogrusal arama: aranan deger list[n]'ye yazilir, boylece dongude
 * sinir denetimi gerekmez. Dizide n + 1 yer olmalidir.
 * Slaytlar: "Uygulama 2: Dogrusal Arama", "seqsearch() Adim Adim".
 * Ornek nottan: list = {4, 8, 2}; 5 aranir (-1), 8 aranir (1). */
#include <stdio.h>

int seqsearch(int list[], int searchnum, int n) {
  int i;
  list[n] = searchnum;          /* bekci */
  for (i = 0; list[i] != searchnum; i++)
    ;
  return (i < n) ? i : -1;
}

int main(void) {  /* sunumda yok */
  int list[4] = {4, 8, 2};      /* 3 oge + bekci yeri */
  printf("seqsearch(list, 5, 3) = %d\n", seqsearch(list, 5, 3));
  printf("seqsearch(list, 8, 3) = %d\n", seqsearch(list, 8, 3));
  return 0;
}

/* Beklenen cikti:
 * seqsearch(list, 5, 3) = -1
 * seqsearch(list, 8, 3) = 1
 */
