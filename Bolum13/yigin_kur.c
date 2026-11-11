/* Asagidan yukari heap kurma: son ic dugumden (n/2) koke dogru her
 * dugum asagi kaydirilir; toplam is O(n).
 * Notlardaki ornek (Tablo 13.14): 5, 3, 8, 9, 1, 12, 7 -> 12, 9, 8, 3, 1, 5, 7.
 * Slaytlar: "Asagidan yukari heap kurma", "Izleme: yigin_kur - 1",
 * "Izleme: yigin_kur - 2". */
#include <stdio.h>

/* sunumda yok: "C tanimlari" slaytindaki oge tipi */
typedef struct {
  int x;          /* öncelik (anahtar) */
  /* diğer alanlar */
} eleman;

void yigin_kur(eleman a[], int n) {
  for (int k = n / 2; k >= 1; k--) {
    eleman deger = a[k];
    int i = k, j = 2 * k;
    while (j <= n) {
      if (j < n && a[j].x < a[j + 1].x) j++;
      if (deger.x >= a[j].x) break;
      a[i] = a[j];
      i = j; j *= 2;
    }
    a[i] = deger;
  }
}

/* sunumda yok: a[1..n]'yi yazar */
static void yazdir(const eleman a[], int n) {
    for (int i = 1; i <= n; i++)
        printf(i == 1 ? "%d" : ", %d", a[i].x);
    printf("\n");
}

int main(void)
{
    /* a[0] kullanilmaz */
    eleman a[8] = {{0}, {5}, {3}, {8}, {9}, {1}, {12}, {7}};
    printf("girdi: ");
    yazdir(a, 7);
    yigin_kur(a, 7);
    printf("heap:  ");
    yazdir(a, 7);
    return 0;
}

/* Beklenen cikti:
 * girdi: 5, 3, 8, 9, 1, 12, 7
 * heap:  12, 9, 8, 3, 1, 5, 7
 */
