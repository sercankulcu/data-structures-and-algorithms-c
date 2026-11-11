/* Saglanabilirlik (SAT) kaba kuvvetle: formul agaci kok sonda (postorder)
 * degerlendirilir; 3 degiskenin 2^3 atamasi m sayacinin bitlerinden uretilir.
 * Formul (nottan): (x1 VE DEGIL x2) VEYA (DEGIL x1 VE x3) VEYA DEGIL x3.
 * Slaytlar: "SAT: Agaci Degerlendirmek", "SAT Kaba Kuvvet Adim Adim".
 * Agaci kuran yardimcilar sunumda yok; ders notundaki surumleri alindi. */
#include <stdio.h>
#include <stdlib.h>

typedef enum { DEGIL, VE, VEYA, DOGRU, YANLIS } mantik;
typedef struct agac *agac_gost;
struct agac {
  agac_gost solcocuk, sagcocuk;
  mantik veri;
  short deger;
};

void kok_sonda_degerlendir(agac_gost L) {
  if (L) {
    kok_sonda_degerlendir(L->solcocuk);
    kok_sonda_degerlendir(L->sagcocuk);
    switch (L->veri) {
      case DEGIL: L->deger = !L->sagcocuk->deger; break;
      case VE:   L->deger = L->solcocuk->deger
                         && L->sagcocuk->deger; break;
      case VEYA: L->deger = L->solcocuk->deger
                         || L->sagcocuk->deger; break;
      case DOGRU:  L->deger = 1; break;
      case YANLIS: L->deger = 0; break;
    }
  }
}

/* sunumda yok (ders notundan): dugum olusturma ve agaci silme */
agac_gost yeni_dugum(mantik v, agac_gost sol, agac_gost sag) {
  agac_gost p = malloc(sizeof *p);
  if (p == NULL) {               /* bellek ayrilamadi */
    fprintf(stderr, "bellek yok\n");
    exit(EXIT_FAILURE);
  }
  p->veri = v;
  p->solcocuk = sol;
  p->sagcocuk = sag;
  p->deger = 0;
  return p;
}

void agac_sil(agac_gost L) {     /* kok sonda: once cocuklar */
  if (L) {
    agac_sil(L->solcocuk);
    agac_sil(L->sagcocuk);
    free(L);
  }
}

/* sunumda yok (ders notundan): formul agaci ve atamanin yerlestirilmesi */
agac_gost y[5];   /* yapraklar: x1, x2, x1, x3, x3 */

agac_gost formul_kur(void) {
  int k;
  for (k = 0; k < 5; k++)
    y[k] = yeni_dugum(YANLIS, NULL, NULL);
  /* (x1 VE DEGIL x2) VEYA (DEGIL x1 VE x3) VEYA DEGIL x3 */
  return yeni_dugum(VEYA,
           yeni_dugum(VEYA,
             yeni_dugum(VE, y[0], yeni_dugum(DEGIL, NULL, y[1])),
             yeni_dugum(VE, yeni_dugum(DEGIL, NULL, y[2]), y[3])),
           yeni_dugum(DEGIL, NULL, y[4]));
}

void yapraklari_yerlestir(agac_gost kok, int x1, int x2, int x3) {
  (void)kok;            /* yapraklara y[] ile dogrudan erisilir */
  y[0]->veri = x1 ? DOGRU : YANLIS;
  y[1]->veri = x2 ? DOGRU : YANLIS;
  y[2]->veri = x1 ? DOGRU : YANLIS;
  y[3]->veri = x3 ? DOGRU : YANLIS;
  y[4]->veri = x3 ? DOGRU : YANLIS;
}

int main(void) {  /* sunumda yok: dongu "SAT Kaba Kuvvet" slaytindan */
  agac_gost kok = formul_kur();
  int m, x1, x2, x3;
  for (m = 0; m < 8; m++) {    /* 2^3 atama */
    x1 = (m >> 2) & 1;
    x2 = (m >> 1) & 1;
    x3 = m & 1;
    yapraklari_yerlestir(kok, x1, x2, x3);
    kok_sonda_degerlendir(kok);
    if (kok->deger)
      printf("%d%d%d\n", x1, x2, x3);
  }
  agac_sil(kok);
  return 0;
}

/* Yalniz 111 atamasi formulu saglamaz. */
/* Beklenen cikti:
 * 000
 * 001
 * 010
 * 011
 * 100
 * 101
 * 110
 */
