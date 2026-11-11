/* Union-find uygulamasi: baglantili bilesen sayma. Her kenarin iki ucunun
 * koku bulunur; kokler farkliysa kumeler birlestirilir ve sayac bir azalir.
 * Notlardaki ornek: 6 dugum, kenarlar (0,1), (2,3), (1,4), (3,2); sonuc 3
 * ({0,1,4}, {2,3}, {5}), son dizi -3 0 -2 2 0 -1.
 * Slayt: "Izleme: bilesen_say". */
#include <stdio.h>

#define N 10   /* sunumda yok: "ata dizisi" slaytindaki boyut */
int ata[N];

/* sunumda yok: "Birlesim_2" slaytindaki agirlikli birlesim */
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

/* sunumda yok: "Kume_Bul_2" slaytindaki yol kisaltmali bulma */
int Kume_Bul_2(int i) {
  int r, s;
  for (r = i; ata[r] >= 0; r = ata[r])
    ;                   /* kökü bul */
  while (i != r) {      /* yolu azalt */
    s = ata[i];         /* i'nin ebeveynini sakla */
    ata[i] = r;         /* i'yi doğrudan köke bağla */
    i = s;              /* ebeveynine geç */
  }
  return r;
}

int bilesen_say(int n, int m, int u[], int v[]) {
  for (int i = 0; i < n; i++) ata[i] = -1;
  int sayi = n;               /* her düğüm ayrı */
  for (int e = 0; e < m; e++) {
    int a = Kume_Bul_2(u[e]), b = Kume_Bul_2(v[e]);
    if (a != b) {             /* farklı bileşen */
      Birlesim_2(a, b);
      sayi--;
    }
  }
  return sayi;
}

int main(void)
{
    int u[] = {0, 2, 1, 3};
    int v[] = {1, 3, 4, 2};
    int i;
    printf("bilesen_say(6, 4, u, v) = %d\n", bilesen_say(6, 4, u, v));
    printf("ata =");
    for (i = 0; i < 6; i++) printf(" %d", ata[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti:
 * bilesen_say(6, 4, u, v) = 3
 * ata = -3 0 -2 2 0 -1
 */
