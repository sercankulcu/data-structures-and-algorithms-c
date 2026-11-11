/* Hizli transpoz: 1. asamada her sutunun oge sayisi (row_terms) ve
 * transpozdaki baslangic konumu (start_pos, onek toplami) bulunur; 2. asamada
 * M bir kez taranir ve her uclu dogrudan yerine yazilir. Ikinci fonksiyon
 * analiz slaytindaki tek dizili surumdur: sayac dizisi yerinde baslangic
 * konumuna cevrilir.
 * Notlardaki ornekler: 3 x 4 matris ve 6 x 6 matris.
 * Slaytlar: "fast_transpose", "fast_transpose() 1. Asama",
 * "fast_transpose() 2. Asama", "fast_transpose Analizi". */
#include <stdio.h>

/* sunumda yok: "Seyrek Matris" slaytindaki tanimlar */
#define MAX_TERMS 101
#define MAX_COL 50   /* azami sütun */
typedef struct {
  int row, col, value;   /* satır, sütun, değer */
} term;

void fast_transpose(term M[], term T[]) {
  int i, j, nc = M[0].col, nt = M[0].value;
  int row_terms[MAX_COL], start_pos[MAX_COL];
  T[0].row = nc;  T[0].col = M[0].row;  T[0].value = nt;
  if (nt <= 0) return;                    /* boş matris */
  for (i = 0; i < nc; i++) row_terms[i] = 0;
  for (i = 1; i <= nt; i++) row_terms[M[i].col]++;
  start_pos[0] = 1;
  for (i = 1; i < nc; i++)
    start_pos[i] = start_pos[i-1] + row_terms[i-1];
  for (i = 1; i <= nt; i++) {
    j = start_pos[M[i].col]++;       /* yerini al, artır */
    T[j].row = M[i].col;  T[j].col = M[i].row;
    T[j].value = M[i].value;
  }
}

/* sunumda yok: fonksiyon basligi, baslik ucluleri ve sayma; slayttaki
 * parca asagida isaretlidir */
void fast_transpose_tek(term M[], term T[]) {
  int i, j, pos, nc = M[0].col, nt = M[0].value;
  int cnt[MAX_COL];
  T[0].row = nc;  T[0].col = M[0].row;  T[0].value = nt;
  if (nt <= 0) return;
  for (i = 0; i < nc; i++) cnt[i] = 0;
  for (i = 1; i <= nt; i++) cnt[M[i].col]++;
  /* --- slayttaki parca --- */
  /* row_terms'ü yerinde start_pos'a çevir */
  for (i = 0, pos = 1; i < nc; i++) {
    int c = cnt[i];      /* bu sütundaki terim sayısı */
    cnt[i] = pos;        /* artık başlangıç konumu */
    pos += c;
  }
  for (i = 1; i <= nt; i++) {
    j = cnt[M[i].col]++;
    T[j].row = M[i].col;  T[j].col = M[i].row;
    T[j].value = M[i].value;
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
  static term M[MAX_TERMS], T[MAX_TERMS], T2[MAX_TERMS];
  const int kucuk[][3] = {{0, 0, 7}, {0, 3, 3}, {1, 1, 4}, {2, 0, 2}};
  const int buyuk[][3] = {{0, 0, 15}, {0, 3, 22}, {0, 5, -15}, {1, 1, 11},
                          {1, 2, 3}, {2, 3, -6}, {4, 0, 91}, {5, 2, 28}};

  doldur(M, 3, 4, kucuk, 4);
  yaz("M", M);
  fast_transpose(M, T);
  yaz("T", T);
  fast_transpose_tek(M, T2);
  yaz("T (tek dizi)", T2);

  doldur(M, 6, 6, buyuk, 8);
  yaz("M", M);
  fast_transpose(M, T);
  yaz("T", T);
  fast_transpose_tek(M, T2);
  yaz("T (tek dizi)", T2);
  return 0;
}

/* Beklenen cikti:
 * M: 3x4, 4 terim: (0,0,7) (0,3,3) (1,1,4) (2,0,2)
 * T: 4x3, 4 terim: (0,0,7) (0,2,2) (1,1,4) (3,0,3)
 * T (tek dizi): 4x3, 4 terim: (0,0,7) (0,2,2) (1,1,4) (3,0,3)
 * M: 6x6, 8 terim: (0,0,15) (0,3,22) (0,5,-15) (1,1,11) (1,2,3) (2,3,-6) (4,0,91) (5,2,28)
 * T: 6x6, 8 terim: (0,0,15) (0,4,91) (1,1,11) (2,1,3) (2,5,28) (3,0,22) (3,2,-6) (5,0,-15)
 * T (tek dizi): 6x6, 8 terim: (0,0,15) (0,4,91) (1,1,11) (2,1,3) (2,5,28) (3,0,22) (3,2,-6) (5,0,-15)
 */
