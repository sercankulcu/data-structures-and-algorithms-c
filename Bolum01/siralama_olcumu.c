/* Secimli siralamanin suresini clock() ile 0..5000 ogeli azalan dizilerde
 * olcmek. Slayt: "Uygulama 1: Siralamayi Olcmek". sort() ve SWAP
 * "Secimli Siralama: C Kodu" slaytindan alindi. */
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 5001
#define ITERATIONS 20
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))  /* sunumda yok: onceki slayttan */
void sort(int list[], int n);   /* secmeli siralama */

int main(void) {
  int i, j, list[MAX_SIZE];
  int sizelist[] = { 0, 100, 300, 600, 900, 1200, 1500, 2000,
    3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800,
    3900, 4000, 5000 };
  clock_t start, stop;  double ms;
  for (i = 0; i < ITERATIONS; i++) {
    for (j = 0; j < sizelist[i]; j++)
      list[j] = sizelist[i] - j;   /* azalan dizi */
    start = clock();
    sort(list, sizelist[i]);
    stop = clock();
    ms = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
    printf("%4d eleman: %6.1f ms\n", sizelist[i], ms);
  }
  return 0;
}

/* sunumda yok: "Secimli Siralama: C Kodu" slaytindaki sort() */
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

/* Sureler makineye ve calistirmaya gore degisir; asagidaki blok bir ornek
 * calistirmadir (Windows, clock() vurusu 1 ms) ve birebir tutmasi beklenmez.
 * Degismeyen: 20 satir, ilk satir 0.0 ms, sure n ile karesel buyur. */
/* Beklenen cikti:
 *    0 eleman:    0.0 ms
 *  100 eleman:    0.0 ms
 *  300 eleman:    0.0 ms
 *  600 eleman:    0.0 ms
 *  900 eleman:    0.0 ms
 * 1200 eleman:    1.0 ms
 * 1500 eleman:    0.0 ms
 * 2000 eleman:    1.0 ms
 * 3000 eleman:    1.0 ms
 * 3100 eleman:    2.0 ms
 * 3200 eleman:    1.0 ms
 * 3300 eleman:    3.0 ms
 * 3400 eleman:    1.0 ms
 * 3500 eleman:    2.0 ms
 * 3600 eleman:    3.0 ms
 * 3700 eleman:    2.0 ms
 * 3800 eleman:    2.0 ms
 * 3900 eleman:    3.0 ms
 * 4000 eleman:    2.0 ms
 * 5000 eleman:    4.0 ms
 */
