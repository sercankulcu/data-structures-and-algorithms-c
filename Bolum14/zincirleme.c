/* Ayri zincirleme: her kova bir bagli listenin basidir; ekleme basa
 * yapilir, arama yalniz kendi kovasinin zincirini yurur, silmede onceki
 * isaretci tutulur (bastaki dugumde kova guncellenir).
 * Notlardaki ornek: MZ = 5, 10 ve 4 eklenir, sonra 12, 7, 22 (hepsi kova 2,
 * zincir 22 -> 7 -> 12); zincir_ara(12) ve (17); zincir_sil(7), ikinci
 * zincir_sil(7) ve bastaki 22'nin silinmesi.
 * Slaytlar: "Zincirleme" (iki slayt), "Izleme: zincir_ekle",
 * "Izleme: zincir_ara", "Izleme: zincir_sil". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MZ 5
typedef struct dugum {
  int anahtar;
  struct dugum *sonraki;
} dugum;
dugum *kova[MZ];           /* hepsi NULL */

bool zincir_ekle(int k) {
  int i = k % MZ;
  dugum *yeni = malloc(sizeof *yeni);
  if (yeni == NULL) return false;  /* bellek yok */
  yeni->anahtar = k;
  yeni->sonraki = kova[i];         /* başa ekle */
  kova[i] = yeni;
  return true;
}

dugum *zincir_ara(int k) {
  dugum *p = kova[k % MZ];
  while (p != NULL && p->anahtar != k)
    p = p->sonraki;
  return p;                 /* NULL: yok */
}

bool zincir_sil(int k) {
  int i = k % MZ;
  dugum *p = kova[i], *onceki = NULL;
  while (p != NULL && p->anahtar != k) {
    onceki = p;
    p = p->sonraki;
  }
  if (p == NULL) return false;           /* yok */
  if (onceki == NULL) kova[i] = p->sonraki;
  else onceki->sonraki = p->sonraki;
  free(p);
  return true;
}

/* sunumda yok: tablonun butun bellegini geri verir (ders notundan) */
void zincir_bosalt(void) {
  for (int i = 0; i < MZ; i++) {
    dugum *p = kova[i];
    while (p != NULL) {
      dugum *sonra = p->sonraki;   /* free'den önce sakla */
      free(p);
      p = sonra;
    }
    kova[i] = NULL;
  }
}

/* sunumda yok: kovalari yazar */
static void yazdir(void) {
    for (int i = 0; i < MZ; i++) {
        printf("kova %d:", i);
        for (dugum *p = kova[i]; p != NULL; p = p->sonraki)
            printf(" %d", p->anahtar);
        printf("\n");
    }
}

int main(void)
{
    int a[] = {10, 4, 12, 7, 22};
    for (int i = 0; i < 5; i++)
        zincir_ekle(a[i]);
    yazdir();
    printf("zincir_ara(12): %s\n", zincir_ara(12) ? "bulundu" : "yok");
    printf("zincir_ara(17): %s\n", zincir_ara(17) ? "bulundu" : "yok");
    printf("zincir_sil(7) = %d\n", zincir_sil(7));
    printf("zincir_sil(7) = %d\n", zincir_sil(7));
    printf("zincir_sil(22) = %d\n", zincir_sil(22));
    yazdir();
    zincir_bosalt();
    return 0;
}

/* Beklenen cikti:
 * kova 0: 10
 * kova 1:
 * kova 2: 22 7 12
 * kova 3:
 * kova 4: 4
 * zincir_ara(12): bulundu
 * zincir_ara(17): yok
 * zincir_sil(7) = 1
 * zincir_sil(7) = 0
 * zincir_sil(22) = 1
 * kova 0: 10
 * kova 1:
 * kova 2: 12
 * kova 3:
 * kova 4: 4
 */
