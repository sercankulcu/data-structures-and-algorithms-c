/* Uclu gosterimde seyrek matris carpimi D = A * B. Once B'nin transpozu
 * (bt) alinir; boylece B'nin sutunlari ardisik satirlar olur. son() bir
 * satirin bittigi yeri bulur, carp() iki satiri sutun alanina gore
 * birlestirerek nokta carpimini hesaplar, sakla() sifir olmayan toplami
 * sonuca yazar.
 * Notlardaki ornekler: A = [[1,0,2],[0,3,0]], B = [[4,0],[0,5],[6,0]]
 * ve carpimi dolu cikan iki 3 x 3 seyrek matris.
 * Slaytlar: "Seyrek Carpim Kodu" (iki blok), "smult() Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: "Seyrek Matris" slaytindaki tanimlar */
#define MAX_TERMS 101
#define MAX_COL 50   /* azami sütun */
typedef struct {
  int row, col, value;   /* satır, sütun, değer */
} term;

/* s'deki terimin satırının bittiği yer */
int son(term t[], int s) {
  int e = s;
  while (e <= t[0].value &&
         t[e].row == t[s].row) e++;
  return e;
}
/* a[x..ex) satırı · b[y..ey) satırı */
int carp(term a[], int x, int ex,
         term b[], int y, int ey) {
  int sum = 0;
  while (x < ex && y < ey)
    if (a[x].col < b[y].col) x++;
    else if (a[x].col > b[y].col) y++;
    else sum += a[x++].value * b[y++].value;
  return sum;
}

void sakla(term d[], int *nd,
      int r, int c, int s) {
  if (s == 0) return;
  if (++*nd >= MAX_TERMS) {
    fprintf(stderr, "Cok terim\n");
    exit(1);
  }
  d[*nd].row = r;
  d[*nd].col = c;
  d[*nd].value = s;
}

void smult(term a[], term bt[], term d[]) {
  int ra, ea, rb, eb, nd = 0;
  for (ra = 1; ra <= a[0].value; ra = ea) {
    ea = son(a, ra);           /* A satırı [ra,ea) */
    for (rb = 1; rb <= bt[0].value; rb = eb) {
      eb = son(bt, rb);        /* B sütunu [rb,eb) */
      sakla(d, &nd, a[ra].row, bt[rb].row,
            carp(a, ra, ea, bt, rb, eb));
    }
  }
  d[0].row = a[0].row;  d[0].col = bt[0].row;
  d[0].value = nd;
}

/* sunumda yok: "fast_transpose" slaytindaki fonksiyon, bt'yi kurmak icin */
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
  static term a[MAX_TERMS], b[MAX_TERMS], bt[MAX_TERMS], d[MAX_TERMS];
  const int a1[][3] = {{0, 0, 1}, {0, 2, 2}, {1, 1, 3}};
  const int b1[][3] = {{0, 0, 4}, {1, 1, 5}, {2, 0, 6}};
  const int a2[][3] = {{0, 0, 1}, {1, 0, 1}, {2, 0, 1}};
  const int b2[][3] = {{0, 0, 1}, {0, 1, 1}, {0, 2, 1}};

  doldur(a, 2, 3, a1, 3);
  doldur(b, 3, 2, b1, 3);
  fast_transpose(b, bt);
  yaz("a", a);
  yaz("bt", bt);
  smult(a, bt, d);
  yaz("d", d);

  doldur(a, 3, 3, a2, 3);
  doldur(b, 3, 3, b2, 3);
  fast_transpose(b, bt);
  yaz("a", a);
  yaz("bt", bt);
  smult(a, bt, d);
  yaz("d", d);
  return 0;
}

/* Beklenen cikti:
 * a: 2x3, 3 terim: (0,0,1) (0,2,2) (1,1,3)
 * bt: 2x3, 3 terim: (0,0,4) (0,2,6) (1,1,5)
 * d: 2x2, 2 terim: (0,0,16) (1,1,15)
 * a: 3x3, 3 terim: (0,0,1) (1,0,1) (2,0,1)
 * bt: 3x3, 3 terim: (0,0,1) (1,0,1) (2,0,1)
 * d: 3x3, 9 terim: (0,0,1) (0,1,1) (0,2,1) (1,0,1) (1,1,1) (1,2,1) (2,0,1) (2,1,1) (2,2,1)
 */
