/* AVL agaci: her dugumde alt agac yuksekligi (yuk), denge faktoru,
 * saga/sola dondurme ve LL, RR, LR, RL durumlarini duzelten avl_ekle.
 * Notlardaki ornekler: 30, 20, 40, 10, 25, 5 (5 eklenince 30'da LL,
 * sag_dondur(30)); Weiss'in 3, 2, 1, 4, 5, 6, 7, 16, 15 dizisi (Tablo 11.9);
 * alistirmadaki 10, 20, 30, 25, 28 (RR, sonra LR).
 * Slaytlar: "AVL Tanimi", "sag_dondur() Adim Adim", "AVL Ekleme Kodu". */
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))  /* sunumda yok: notta verilen makro */

typedef struct avl *avl_gost;
struct avl {
    int      veri;
    int      yuk;        /* alt ağaç yüksekliği */
    avl_gost sol, sag;
};
int yuk(avl_gost t) { return t ? t->yuk : 0; }
int denge(avl_gost t) {
    return yuk(t->sol) - yuk(t->sag);
}

avl_gost sag_dondur(avl_gost k2) {  // LL
  avl_gost k1 = k2->sol;
  k2->sol = k1->sag;
  k1->sag = k2;
  k2->yuk = 1 + MAX(yuk(k2->sol), yuk(k2->sag));
  k1->yuk = 1 + MAX(yuk(k1->sol), k2->yuk);
  return k1;                       // yeni kök
}

/* sunumda yok: sola dondurme ve yeni_avl (ders notundaki surumler) */
avl_gost sol_dondur(avl_gost k1) {  // RR
  avl_gost k2 = k1->sag;
  k1->sag = k2->sol;
  k2->sol = k1;
  k1->yuk = 1 + MAX(yuk(k1->sol), yuk(k1->sag));
  k2->yuk = 1 + MAX(k1->yuk, yuk(k2->sag));
  return k2;                       // yeni kök
}
avl_gost yeni_avl(int x) {
  avl_gost t = malloc(sizeof *t);
  if (!t) { fprintf(stderr, "Bellek yetersiz\n"); exit(EXIT_FAILURE); }
  t->veri = x; t->yuk = 1;
  t->sol = t->sag = NULL;
  return t;
}

avl_gost avl_ekle(avl_gost t, int x) {
  if (!t) return yeni_avl(x);              /* malloc, yuk = 1        */
  if (x < t->veri)      t->sol = avl_ekle(t->sol, x);
  else if (x > t->veri) t->sag = avl_ekle(t->sag, x);
  else return t;                           /* tekrar eden değer yok  */
  t->yuk = 1 + MAX(yuk(t->sol), yuk(t->sag));
  int d = denge(t);
  if (d >  1 && x < t->sol->veri) return sag_dondur(t);            /* LL */
  if (d < -1 && x > t->sag->veri) return sol_dondur(t);            /* RR */
  if (d >  1) { t->sol = sol_dondur(t->sol); return sag_dondur(t); } /* LR */
  if (d < -1) { t->sag = sag_dondur(t->sag); return sol_dondur(t); } /* RL */
  return t;
}

/* sunumda yok: agaci kok(sol, sag) biciminde yazar, bos alt agac "-" */
static void yaz(avl_gost t) {
    if (!t) { printf("-"); return; }
    printf("%d", t->veri);
    if (t->sol || t->sag) {
        printf("(");
        yaz(t->sol);
        printf(", ");
        yaz(t->sag);
        printf(")");
    }
}

/* sunumda yok: agaci bellege iade eder */
static void avl_sil(avl_gost t) {
    if (t) {
        avl_sil(t->sol);
        avl_sil(t->sag);
        free(t);
    }
}

/* sunumda yok: degerleri sirayla ekler, her adimda agaci yazar */
static void dizi_ekle(const int a[], int n) {
    avl_gost kok = NULL;
    for (int i = 0; i < n; i++) {
        kok = avl_ekle(kok, a[i]);
        printf("+%d: ", a[i]);
        yaz(kok);
        printf("\n");
    }
    printf("yukseklik = %d, kokte denge = %d\n", yuk(kok), denge(kok));
    avl_sil(kok);
}

int main(void)
{
    int a[] = {30, 20, 40, 10, 25, 5};
    int b[] = {3, 2, 1, 4, 5, 6, 7, 16, 15};
    int c[] = {10, 20, 30, 25, 28};
    dizi_ekle(a, 6);
    dizi_ekle(b, 9);
    dizi_ekle(c, 5);
    return 0;
}

/* Beklenen cikti:
 * +30: 30
 * +20: 30(20, -)
 * +40: 30(20, 40)
 * +10: 30(20(10, -), 40)
 * +25: 30(20(10, 25), 40)
 * +5: 20(10(5, -), 30(25, 40))
 * yukseklik = 3, kokte denge = 0
 * +3: 3
 * +2: 3(2, -)
 * +1: 2(1, 3)
 * +4: 2(1, 3(-, 4))
 * +5: 2(1, 4(3, 5))
 * +6: 4(2(1, 3), 5(-, 6))
 * +7: 4(2(1, 3), 6(5, 7))
 * +16: 4(2(1, 3), 6(5, 7(-, 16)))
 * +15: 4(2(1, 3), 6(5, 15(7, 16)))
 * yukseklik = 4, kokte denge = -1
 * +10: 10
 * +20: 10(-, 20)
 * +30: 20(10, 30)
 * +25: 20(10, 30(25, -))
 * +28: 20(10, 28(25, 30))
 * yukseklik = 3, kokte denge = -1
 */
