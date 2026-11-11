/* Seyrek matrisin uclu (satir, sutun, deger) gosterimi ve basit transpoz:
 * M'nin her sutunu icin butun uclulere bakilir; sonuc kendiliginden satir
 * sirasindadir. M[0] baslik: satir sayisi, sutun sayisi, dolu oge sayisi.
 * Notlardaki ornekler: 3 x 4 matris (4 dolu oge) ve 6 x 6 matris (8 dolu oge).
 * Slaytlar: "Seyrek Matris", "transpose() Adim Adim". */
#include <stdio.h>

#define MAX_TERMS 101
#define MAX_COL 50   /* azami sütun */
typedef struct {
  int row, col, value;   /* satır, sütun, değer */
} term;
term M[MAX_TERMS];

void transpose(term M[], term T[]) {
  int n = M[0].value, i, j, cur;
  T[0].row = M[0].col;  T[0].col = M[0].row;
  T[0].value = n;
  if (n > 0) {
    cur = 1;                       /* T'de sıradaki */
    for (i = 0; i < M[0].col; i++)     /* her sütun */
      for (j = 1; j <= n; j++)         /* her terim */
        if (M[j].col == i) {
          T[cur].row = M[j].col; T[cur].col = M[j].row;
          T[cur].value = M[j].value;  cur++;
        }
  }
}

/* sunumda yok: uclu tabloyu yazar */
static void yaz(const char *ad, const term t[]) {
  printf("%s: %dx%d, %d terim:", ad, t[0].row, t[0].col, t[0].value);
  for (int i = 1; i <= t[0].value; i++)
    printf(" (%d,%d,%d)", t[i].row, t[i].col, t[i].value);
  printf("\n");
}

/* sunumda yok: sayi dizisinden uclu tabloyu doldurur */
static void doldur(term t[], int rows, int cols, const int u[][3], int n) {
  t[0].row = rows; t[0].col = cols; t[0].value = n;
  for (int i = 0; i < n; i++) {
    t[i + 1].row = u[i][0]; t[i + 1].col = u[i][1]; t[i + 1].value = u[i][2];
  }
}

int main(void)
{
  static term T[MAX_TERMS];
  const int kucuk[][3] = {{0, 0, 7}, {0, 3, 3}, {1, 1, 4}, {2, 0, 2}};
  const int buyuk[][3] = {{0, 0, 15}, {0, 3, 22}, {0, 5, -15}, {1, 1, 11},
                          {1, 2, 3}, {2, 3, -6}, {4, 0, 91}, {5, 2, 28}};

  doldur(M, 3, 4, kucuk, 4);
  yaz("M", M);
  transpose(M, T);
  yaz("T", T);

  doldur(M, 6, 6, buyuk, 8);
  yaz("M", M);
  transpose(M, T);
  yaz("T", T);
  return 0;
}

/* Beklenen cikti:
 * M: 3x4, 4 terim: (0,0,7) (0,3,3) (1,1,4) (2,0,2)
 * T: 4x3, 4 terim: (0,0,7) (0,2,2) (1,1,4) (3,0,3)
 * M: 6x6, 8 terim: (0,0,15) (0,3,22) (0,5,-15) (1,1,11) (1,2,3) (2,3,-6) (4,0,91) (5,2,28)
 * T: 6x6, 8 terim: (0,0,15) (0,4,91) (1,1,11) (2,1,3) (2,5,28) (3,0,22) (3,2,-6) (5,0,-15)
 */
