/* struct, ic ice ve kendine basvuran yapilar, etiketli union.
 * Yapi atamasi alan alan kopyalar; == ile karsilastirma derlenmez.
 * Slaytlar: "struct", "Ic Ice ve Kendine Basvuran", "union ve Hizalama".
 * sizeof degerleri 64 bit Linux icindir (nottaki surucuyle ayni). */
#include <stdio.h>
#include <string.h>  /* sunumda yok: strcpy icin */

typedef struct {
  char ad[10];
  int yas;
  float maas;
} insan;

typedef struct {
  int gun, ay, yil;
} tarih;

typedef struct {
  char ad[10];
  tarih dogum;          /* iç içe yapı */
} kisi;

typedef struct liste {
  char veri;
  struct liste *bag;    /* kendine başvuru */
} liste;

typedef struct {
  enum { KADIN, ERKEK } tur;   /* etiket */
  union {
    int cocuk_sayisi;          /* KADIN ise */
    int sakal;                 /* ERKEK ise */
  } u;
} cinsiyet;

int main(void) {  /* sunumda yok */
  /* "struct" slayti */
  insan k1, k2;
  memset(&k1, 0, sizeof k1);   /* sunumda yok: dolgu baytlari dahil sifirla */
  strcpy(k1.ad, "Ali");
  k1.yas = 21;
  k1.maas = 3500.0f;
  k2 = k1;          /* alan alan kopyalanır */
  /* if (k1 == k2) -> DERLENMEZ */
  printf("k2: %s %d %.1f\n", k2.ad, k2.yas, k2.maas);

  /* "Ic Ice ve Kendine Basvuran" slayti */
  {
    kisi k;
    liste a1, a2, a3, *q;
    strcpy(k.ad, "Ayse");
    k.dogum.gun = 12; k.dogum.ay = 5;
    k.dogum.yil = 2004;
    printf("k: %s %d.%d.%d\n", k.ad, k.dogum.gun, k.dogum.ay, k.dogum.yil);

    a1.veri = 'a'; a1.bag = &a2;
    a2.veri = 'b'; a2.bag = &a3;
    a3.veri = 'c'; a3.bag = NULL;
    printf("liste:");
    for (q = &a1; q != NULL; q = q->bag) printf(" %c", q->veri);
    printf("\n");
  }

  /* "union ve Hizalama" slayti */
  {
    cinsiyet c;
    c.tur = ERKEK;
    c.u.sakal = 0;   /* yalnız etiketle uyumlu alanı oku */
    if (c.tur == ERKEK) printf("ERKEK, sakal = %d\n", c.u.sakal);
    else printf("KADIN, cocuk_sayisi = %d\n", c.u.cocuk_sayisi);
  }

  printf("sizeof: insan %zu, kisi %zu, liste %zu\n",
         sizeof(insan), sizeof(kisi), sizeof(liste));
  return 0;
}

/* Beklenen cikti:
 * k2: Ali 21 3500.0
 * k: Ayse 12.5.2004
 * liste: a b c
 * ERKEK, sakal = 0
 * sizeof: insan 20, kisi 24, liste 16
 */
