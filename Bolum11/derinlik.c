/* Agac derinligi: yerel sol/sag degiskenli ozyinelemeli derinlik ve
 * kuresel degisken kullanmadan duzey duzey gezen yinelemeli derinlik_d.
 * Notlardaki ornekler: A(B(D, -), C(E(F, -), -)) agaci (derinlik 4), ayni
 * dokuz degerin iki ekleme sirasi (derinlik 4 ve 6) ve bos agac.
 * Slaytlar: "derinlik() Adim Adim", "Yinelemeli Derinlik". */
#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))  /* sunumda yok: notta verilen makro */
#define MAX_SIZE 100                       /* sunumda yok: kuyruk boyu */

typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};

/* sunumda yok: ogeal'in govdesi (ders notundaki gerceklemesi) */
agac_gost ogeal(void) {
    agac_gost r = malloc(sizeof *r);
    if (!r) {
        fprintf(stderr, "Bellek yetersiz\n");
        exit(EXIT_FAILURE);
    }
    r->solcocuk = r->sagcocuk = NULL;
    return r;
}

/* sunumda yok: agaci kurmak icin "Neden agac_gost *L" slaytindaki ekle */
agac_gost ekle(agac_gost L, int x) {
  if (!L) {
    L = ogeal();
    L->veri = x;
  } else if (x < L->veri)
    L->solcocuk = ekle(L->solcocuk, x);
  else if (x > L->veri)
    L->sagcocuk = ekle(L->sagcocuk, x);
  return L;        /* kok = ekle(kok, x); */
}

int derinlik(agac_gost L) {
  int sol, sag;
  if (L) {                   // işaretçi NULL mı
    sol = derinlik(L->solcocuk);
    sag = derinlik(L->sagcocuk);
    return MAX(sol, sag) + 1;
  }
  else return 0;             // uç yaprağa ulaşıldı
}

/* global değişkensiz yinelemeli çözüm:
   düzey düzey gezin, düzeyleri say */
int derinlik_d(agac_gost L) {
  agac_gost k[MAX_SIZE];
  int on = 0, arka = 0, d = 0;
  if (L) k[arka++] = L;
  while (on < arka) {          /* bir düzey */
    int son = arka;
    d++;
    for (; on < son; on++) {
      if (k[on]->solcocuk) k[arka++] = k[on]->solcocuk;
      if (k[on]->sagcocuk) k[arka++] = k[on]->sagcocuk;
    }
  }
  return d;       /* MAX_SIZE >= n olmalı */
}

/* sunumda yok: harf verili tek dugum */
static agac_gost dugum_yap(int x) {
    agac_gost r = ogeal();
    r->veri = x;
    return r;
}

/* sunumda yok: agaci bellege iade eder (kok sonda) */
static void agac_sil(agac_gost L) {
    if (L) {
        agac_sil(L->solcocuk);
        agac_sil(L->sagcocuk);
        free(L);
    }
}

/* sunumda yok: iki yordamin sonucunu yazar */
static void yaz(const char *ad, agac_gost L) {
    printf("%s: derinlik = %d, derinlik_d = %d\n",
           ad, derinlik(L), derinlik_d(L));
}

int main(void)
{
    /* A(B(D, -), C(E(F, -), -)) */
    agac_gost A = dugum_yap('A');
    A->solcocuk = dugum_yap('B');
    A->sagcocuk = dugum_yap('C');
    A->solcocuk->solcocuk = dugum_yap('D');
    A->sagcocuk->solcocuk = dugum_yap('E');
    A->sagcocuk->solcocuk->solcocuk = dugum_yap('F');
    yaz("A..F agaci", A);

    int sira1[] = {47, 55, 49, 26, 34, 17, 52, 84, 93};
    int sira2[] = {26, 17, 47, 93, 84, 52, 34, 55, 49};
    agac_gost T1 = NULL, T2 = NULL;
    for (int i = 0; i < 9; i++) {
        T1 = ekle(T1, sira1[i]);
        T2 = ekle(T2, sira2[i]);
    }
    yaz("47 ile baslayan sira", T1);
    yaz("26 ile baslayan sira", T2);
    yaz("bos agac", NULL);

    agac_sil(A);
    agac_sil(T1);
    agac_sil(T2);
    return 0;
}

/* Beklenen cikti:
 * A..F agaci: derinlik = 4, derinlik_d = 4
 * 47 ile baslayan sira: derinlik = 4, derinlik_d = 4
 * 26 ile baslayan sira: derinlik = 6, derinlik_d = 6
 * bos agac: derinlik = 0, derinlik_d = 0
 */
