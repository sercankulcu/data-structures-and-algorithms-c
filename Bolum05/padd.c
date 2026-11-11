/* Polinomun 2. gosterimi: butun polinomlarin terimleri tek bir P dizisinde,
 * bir polinom P[start..finish] araligidir. padd iki polinomu birlestirme
 * gibi toplar; sonucu avail'den baslayarak dizinin sonuna yazar.
 * Notlardaki iki ornek: (4x^3 + 2x^2 + 5) + (3x^3 - 2x^2 + x) ve
 * (3x^20 + 2x^5 + 4) + (x^5 + 10x^3 + 3x^2 + 1).
 * Slaytlar: "2. Yontem: Terim Dizisi", "padd Fikri", "padd() Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101   /* azami terim sayısı */
typedef struct {
  float coef;            /* katsayı */
  int expon;             /* üs */
} polynomial;
polynomial P[MAX_TERMS]; /* tüm polinomlar burada */
int avail = 0;           /* ilk boş konum */

#define COMPARE(x, y) \
  ((x) < (y) ? -1 : (y) < (x) ? 1 : 0)

void attach(float coef, int expon) {
  if (avail >= MAX_TERMS) {
    fprintf(stderr, "Dizi tasmasi!\n"); exit(1);
  }
  P[avail].coef = coef;
  P[avail++].expon = expon;
}
#define EK(k) attach(P[k].coef, P[k].expon)

void padd(int sa,int fa,int sb,int fb,int*sd,int*fd){
  float c; *sd = avail;               /* D'nin başı */
  while (sa <= fa && sb <= fb)
    switch (COMPARE(P[sa].expon, P[sb].expon)) {
    case -1: EK(sb); sb++; break;     /* B büyük */
    case  1: EK(sa); sa++; break;     /* A büyük */
    case  0: c = P[sa].coef + P[sb].coef;
      if (c) attach(c, P[sa].expon); /* 0: ekleme */
      sa++; sb++;
    }
  for (; sa <= fa; sa++) EK(sa);      /* A'da kalan */
  for (; sb <= fb; sb++) EK(sb);      /* B'de kalan */
  *fd = avail - 1;
}

/* sunumda yok: n terimi attach ile dizinin sonuna yazar, baslangici dondurur */
static int yukle(const float c[], const int e[], int n) {
  int s = avail;
  for (int i = 0; i < n; i++) attach(c[i], e[i]);
  return s;
}

/* sunumda yok: P[s..f] polinomunu yazar */
static void yaz(const char *ad, int s, int f) {
  printf("%s =", ad);
  for (int k = s; k <= f; k++) {
    float c = P[k].coef;
    if (k == s) printf(" %gx^%d", c, P[k].expon);
    else printf(" %c %gx^%d", c < 0 ? '-' : '+', c < 0 ? -c : c, P[k].expon);
  }
  printf("\n");
}

int main(void)
{
  float ac[] = {4, 2, 5};     int ae[] = {3, 2, 0};
  float bc[] = {3, -2, 1};    int be[] = {3, 2, 1};
  float a2c[] = {3, 2, 4};    int a2e[] = {20, 5, 0};
  float b2c[] = {1, 10, 3, 1}; int b2e[] = {5, 3, 2, 0};
  int sa, sb, sd, fd;

  sa = yukle(ac, ae, 3);                 /* P[0..2] */
  sb = yukle(bc, be, 3);                 /* P[3..5], avail = 6 */
  yaz("A", sa, sa + 2);
  yaz("B", sb, sb + 2);
  padd(sa, sa + 2, sb, sb + 2, &sd, &fd);
  yaz("D", sd, fd);
  printf("sd = %d, fd = %d, avail = %d\n", sd, fd, avail);

  avail = 0;                             /* ikinci ornek: dizi bastan kullanilir */
  sa = yukle(a2c, a2e, 3);               /* P[0..2] */
  sb = yukle(b2c, b2e, 4);               /* P[3..6], avail = 7 */
  yaz("A", sa, sa + 2);
  yaz("B", sb, sb + 3);
  padd(sa, sa + 2, sb, sb + 3, &sd, &fd);
  yaz("D", sd, fd);
  printf("sd = %d, fd = %d, avail = %d\n", sd, fd, avail);
  return 0;
}

/* Beklenen cikti:
 * A = 4x^3 + 2x^2 + 5x^0
 * B = 3x^3 - 2x^2 + 1x^1
 * D = 7x^3 + 1x^1 + 5x^0
 * sd = 6, fd = 8, avail = 9
 * A = 3x^20 + 2x^5 + 4x^0
 * B = 1x^5 + 10x^3 + 3x^2 + 1x^0
 * D = 3x^20 + 3x^5 + 10x^3 + 3x^2 + 5x^0
 * sd = 7, fd = 11, avail = 12
 */
