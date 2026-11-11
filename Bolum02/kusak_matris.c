/* Kusak (band) matris: kosegen cevresindeki a + b - 1 kusak, en alttaki
 * kusaktan baslayarak kusak[] dizisinde saklanir; ara[] her kusagin
 * baslangicini tutar. kusak_basi() ayni baslangici formulle verir.
 * Slaytlar: "KusakMatrisKur() Adim Adim" (ve devami), "KusakMatrisEris()
 * Adim Adim", "Analiz ve Odev 1". Ornek nottan (Ornek 2.3): n = 4, a = 3,
 * b = 2; girdi 6 10 3 7 11 1 4 8 12 2 5 9. */
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100  /* sunumda yok: "AltUcgenOku" slaytindaki sinir */

/* sunumda yok: scanf yerine sabit girdi (stdin bos) */
static const int girdi[] = {6, 10, 3, 7, 11, 1, 4, 8, 12, 2, 5, 9};
static int okunan = 0;
static void oku(int *p) { *p = girdi[okunan++]; }

void KusakMatrisKur(int kusak[], int ara[],
                    int n, int a, int b) {
  int i, k, toplamoge = 0;   /* önceki kuşaklar */
  if (n*(a+b-1) - a*(a-1)/2 - b*(b-1)/2 > MAX_SIZE) {
    printf("Bellek yetersiz!\n"); exit(-1);
  }
  for (i = 1 - a; i <= b - 1; i++) {  /* kuşak kuşak */
    ara[i + a - 1] = toplamoge;     /* kuşak başı */
    for (k = 0; k <= n - abs(i) - 1; k++)
      oku(&kusak[ara[i + a - 1] + k]);  /* sunumda: scanf("%d", &kusak[...]); */
    toplamoge += n - abs(i);
  }
}

int KusakMatrisEris(int i, int j, int n, int a,
                    int b, int ara[]) {
  if (i < 0 || j < 0 || i >= n || j >= n) {
    printf("Indis tasmasi\n"); return -3;
  } else if (j - i >= 1) {         /* üst üçgen */
    if (j - i < b)               /* geçerli kuşak */
      return ara[j - i + a - 1] + i;
    else return -1;              /* üst sabit bölge */
  } else if (i - j < a)          /* köşegen / alt */
    return ara[j - i + a - 1] + j;
  else
    return -2;                   /* alt sabit bölge */
}

/* t: kuşak no (1-a..b-1); ara[t+a-1] ile aynı */
int kusak_basi(int t, int n, int a) {
  if (t <= 0)                     /* alt kuşaklar */
    return (t + a - 1) * n
           - (a * (a - 1) + t * (1 - t)) / 2;
  return (a - 1) * n - a * (a - 1) / 2  /* t=0 başı */
         + t * n - t * (t - 1) / 2;
}

int main(void) {  /* sunumda yok */
  int kusak[MAX_SIZE], ara[MAX_SIZE];
  int n = 4, a = 3, b = 2, i, j, k, t;
  int sorgu[4][2] = {{3, 1}, {1, 2}, {0, 3}, {3, 0}};

  KusakMatrisKur(kusak, ara, n, a, b);
  printf("ara:");
  for (k = 0; k < a + b - 1; k++) printf(" %d", ara[k]);
  printf("\nkusak:");
  for (k = 0; k < 12; k++) printf(" %d", kusak[k]);
  printf("\n");

  for (k = 0; k < 4; k++) {
    int s = KusakMatrisEris(sorgu[k][0], sorgu[k][1], n, a, b, ara);
    printf("d%d%d -> %d", sorgu[k][0], sorgu[k][1], s);
    if (s >= 0) printf(" (deger %d)", kusak[s]);
    printf("\n");
  }

  printf("kusak_basi:");
  for (t = 1 - a; t <= b - 1; t++) printf(" %d", kusak_basi(t, n, a));
  printf("\n");

  printf("matris (kusak disi 0):\n");
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      int s = KusakMatrisEris(i, j, n, a, b, ara);
      printf("%3d", s >= 0 ? kusak[s] : 0);
    }
    printf("\n");
  }
  return 0;
}

/* Beklenen cikti:
 * ara: 0 2 5 9
 * kusak: 6 10 3 7 11 1 4 8 12 2 5 9
 * d31 -> 1 (deger 10)
 * d12 -> 10 (deger 5)
 * d03 -> -1
 * d30 -> -2
 * kusak_basi: 0 2 5 9
 * matris (kusak disi 0):
 *   1  2  0  0
 *   3  4  5  0
 *   6  7  8  9
 *   0 10 11 12
 */
