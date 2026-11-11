/* Secimli siralama (selection sort) ve SWAP makrosu. Her turda
 * list[i..n-1] araligindaki en kucuk oge list[i] ile takas edilir.
 * Slaytlar: "Secimli Siralama: C Kodu" (iki blok), "Hatali sort() Surumu"
 * (yalniz yorumda). Ornek dizi nottan: {29, 10, 14, 37, 13}. */
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
void sort(int list[], int n);

int main(void) {
  int i, n, list[MAX_SIZE];
  int ornek[] = {29, 10, 14, 37, 13};  /* sunumda yok: nottaki ornek */
  /* sunumda: printf("Dizi boyunu giriniz: ");
   *          if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE) ...
   * Klavye girdisi yok; n sabit verildi. */
  n = 5;
  if (n < 1 || n > MAX_SIZE) {
    printf("Hatali n degeri!\n");
    return 1;
  }
  /* sunumda: list[i] = rand() % 100; burada nottaki ornek kullanildi */
  for (i = 0; i < n; i++) list[i] = ornek[i];
  sort(list, n);
  for (i = 0; i < n; i++) printf("%d ", list[i]);
  printf("\n");  /* sunumda yok */
  return 0;
}

void sort(int list[], int n) {
  int i, j, min, temp;
  for (i = 0; i < n - 1; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
      if (list[j] < list[min])
        min = j;
    SWAP(list[i], list[min], temp);
  }
}

/* Slayttaki hatali surum (calistirilmaz). Diziyi yine siralar ama secimli
 * siralama degildir: ic dongu j = 0'dan baslar, > ile en buyuk aranir ve
 * takas ic dongunun icinde yapilir. {29, 10, 14, 37, 13} icin 25
 * karsilastirma ve 7 takas yapar (dogru surum: 10 ve 3).
 *
 * void sort(int list[], int n) {
 *   int i, j, min, temp;
 *   for (i = 0; i < n; i++) {
 *     min = i;
 *     for (j = 0; j < n; j++)
 *       if (list[j] > list[min]) {
 *         min = j;
 *         SWAP(list[i], list[min], temp);
 *       }
 *   }
 * }
 */

/* Beklenen cikti:
 * 10 13 14 29 37
 */
