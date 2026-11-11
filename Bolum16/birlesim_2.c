/* Agirlikli birlesim kurali (Birlesim_2): kokte -(dugum sayisi) tutulur, az
 * dugumlu agac cok dugumlunun altina baglanir; agac yuksekligi en cok
 * floor(lg n) + 1 olur.
 * Notlardaki ornek: 8 tek ogeli kume; Birlesim_2(0,1), (2,3), (4,5), (6,7),
 * (0,2), (4,6), (0,4).
 * Slaytlar: "Birlesim_2", "Izleme: Birlesim_2 - 1", "Izleme: Birlesim_2 - 2". */
#include <stdio.h>

#define N 10   /* sunumda yok: "ata dizisi" slaytindaki boyut */
int ata[N];

void Birlesim_2(int i, int j) {
  /* ağırlıklı kural; i ve j kök olmalı */
  int p = ata[i] + ata[j];  /* -(toplam düğüm) */
  if (ata[i] > ata[j]) {    /* i'de daha az düğüm */
    ata[i] = j;             /* i'yi j'ye bağla */
    ata[j] = p;             /* j'nin sayısını günle */
  } else {                  /* j'de az ya da eşit */
    ata[j] = i;
    ata[i] = p;
  }
}

int main(void)
{
    static const int cift[7][2] = {
        {0, 1}, {2, 3}, {4, 5}, {6, 7}, {0, 2}, {4, 6}, {0, 4}
    };
    int i, c, n = 8;
    for (i = 0; i < n; i++) ata[i] = -1;
    for (c = 0; c < 7; c++) {
        Birlesim_2(cift[c][0], cift[c][1]);
        printf("Birlesim_2(%d, %d): ata =", cift[c][0], cift[c][1]);
        for (i = 0; i < n; i++) printf(" %d", ata[i]);
        printf("\n");
    }
    return 0;
}

/* Beklenen cikti:
 * Birlesim_2(0, 1): ata = -2 0 -1 -1 -1 -1 -1 -1
 * Birlesim_2(2, 3): ata = -2 0 -2 2 -1 -1 -1 -1
 * Birlesim_2(4, 5): ata = -2 0 -2 2 -2 4 -1 -1
 * Birlesim_2(6, 7): ata = -2 0 -2 2 -2 4 -2 6
 * Birlesim_2(0, 2): ata = -4 0 0 2 -2 4 -2 6
 * Birlesim_2(4, 6): ata = -4 0 0 2 -4 4 4 6
 * Birlesim_2(0, 4): ata = -8 0 0 2 0 4 4 6
 */
