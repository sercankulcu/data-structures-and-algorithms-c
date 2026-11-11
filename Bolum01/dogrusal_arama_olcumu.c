/* Tekrarli olcum: kisa suren seqsearch() her boyda runtimes[i] kez
 * calistirilir, toplam sure tekrar sayisina bolunur (mikro saniye / arama).
 * Slayt: "Uygulama 2: Dogrusal Arama" (olcum parcasi). Parcanin cevresindeki
 * program (diziler, donguler, yazdirma) sunumda yok; tekrar sayilari notta
 * anlatildigi gibi kucuk boylarda buyuk (500000), buyuk boylarda kucuk
 * (5000) secildi. */
#include <stdio.h>
#include <time.h>
#define MAX_SIZE 5001  /* sunumda yok: 5000 oge + bekci */

/* sunumda yok: "Uygulama 2: Dogrusal Arama" slaytindaki seqsearch() */
int seqsearch(int list[], int searchnum, int n) {
  int i;
  list[n] = searchnum;          /* bekci */
  for (i = 0; list[i] != searchnum; i++)
    ;
  return (i < n) ? i : -1;
}

int main(void) {  /* sunumda yok: olcum parcasini saran program */
  int i, j, pos = 0, list[MAX_SIZE];
  int sizelist[] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
    200, 400, 600, 800, 1000, 2000, 3000, 4000, 5000 };
  long runtimes[] = { 500000, 500000, 500000, 300000, 250000, 200000,
    160000, 140000, 120000, 110000, 100000, 50000, 25000, 16000, 12000,
    10000, 10000, 8000, 6000, 5000 };
  clock_t start, stop;
  double total, ort;
  for (j = 0; j < MAX_SIZE; j++)
    list[j] = j;                    /* -1 hic bulunmaz: hep en kotu durum */
  for (i = 0; i < 20; i++) {
    /* sunumdaki parca: */
    start = clock();
    for (j = 0; j < runtimes[i]; j++)
      pos = seqsearch(list, -1, sizelist[i]);
    stop = clock();
    total = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
    ort = 1000.0 * total / runtimes[i];  /* mikro sn */
    list[sizelist[i]] = sizelist[i];  /* bekciyi sil */
    /* parca sonu */
    printf("%4d eleman: pos = %d, %8.3f us / arama\n", sizelist[i], pos, ort);
  }
  return 0;
}

/* Sureler makineye ve calistirmaya gore degisir; asagidaki blok bir ornek
 * calistirmadir ve birebir tutmasi beklenmez. Degismeyen: 20 satir, pos hep
 * -1, arama basina sure n ile dogrusal buyur. */
/* Beklenen cikti:
 *    0 eleman: pos = -1,    0.000 us / arama
 *   10 eleman: pos = -1,    0.004 us / arama
 *   20 eleman: pos = -1,    0.010 us / arama
 *   30 eleman: pos = -1,    0.017 us / arama
 *   40 eleman: pos = -1,    0.020 us / arama
 *   50 eleman: pos = -1,    0.020 us / arama
 *   60 eleman: pos = -1,    0.025 us / arama
 *   70 eleman: pos = -1,    0.036 us / arama
 *   80 eleman: pos = -1,    0.033 us / arama
 *   90 eleman: pos = -1,    0.036 us / arama
 *  100 eleman: pos = -1,    0.050 us / arama
 *  200 eleman: pos = -1,    0.060 us / arama
 *  400 eleman: pos = -1,    0.120 us / arama
 *  600 eleman: pos = -1,    0.188 us / arama
 *  800 eleman: pos = -1,    0.250 us / arama
 * 1000 eleman: pos = -1,    0.300 us / arama
 * 2000 eleman: pos = -1,    0.500 us / arama
 * 3000 eleman: pos = -1,    0.750 us / arama
 * 4000 eleman: pos = -1,    1.000 us / arama
 * 5000 eleman: pos = -1,    1.200 us / arama
 */
