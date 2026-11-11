/* Acik adresleme, dogrusal yoklama: ekleme ev adresinden baslayip ilk BOS
 * ya da SILINDI yuvaya yazar; arama ilk BOS yuvada durur; silme yuvayi
 * SILINDI isaretler ki arkadaki anahtarlarin yolu kesilmesin.
 * Notlardaki ornek: M = 11, 22, 1, 13, 11, 24, 33 eklenir (ekle(33) yuva 5);
 * ara(24) = 4, ara(44) = -1; sil(13), ardindan ara(24) yine 4 bulur.
 * Slaytlar: "Acik adresleme: C", "Izleme: ekle(33)",
 * "Izleme: ara(24), ara(44)", "Izleme: sil(13), ara(24)". */
#include <stdio.h>
#include <stdbool.h>

#define M 11
typedef enum { BOS, DOLU, SILINDI } durum_t;
typedef struct {
  int anahtar;          /* anahtar >= 0 varsayılır */
  durum_t durum;
} yuva;
yuva tablo[M];          /* global: hepsi 0 = BOS */

int ekle(int k) {
  int i = k % M;                 /* ev adresi */
  for (int d = 0; d < M; d++, i = (i + 1) % M) {
    if (tablo[i].durum != DOLU) {  /* BOS/SILINDI */
      tablo[i].anahtar = k;
      tablo[i].durum = DOLU;
      return i;
    }
  }
  return -1;                     /* tablo dolu */
}

int ara(int k) {
  int i = k % M;
  for (int d = 0; d < M; d++, i = (i + 1) % M) {
    if (tablo[i].durum == BOS) return -1;
    if (tablo[i].durum == DOLU &&
        tablo[i].anahtar == k) return i;
  }
  return -1;
}
bool sil(int k) {
  int i = ara(k);
  if (i < 0) return false;
  tablo[i].durum = SILINDI;   /* silindi işareti */
  return true;
}

/* sunumda yok: tabloyu yazar; BOS ".", SILINDI "x" */
static void yazdir(void) {
    printf("tablo:");
    for (int i = 0; i < M; i++) {
        if (tablo[i].durum == DOLU) printf(" %d", tablo[i].anahtar);
        else if (tablo[i].durum == BOS) printf(" .");
        else printf(" x");
    }
    printf("\n");
}

int main(void)
{
    int a[] = {22, 1, 13, 11, 24, 33};
    for (int i = 0; i < 6; i++)
        printf("ekle(%d) = %d\n", a[i], ekle(a[i]));
    yazdir();
    printf("ara(24) = %d\n", ara(24));
    printf("ara(44) = %d\n", ara(44));
    printf("sil(13) = %d\n", sil(13));
    yazdir();
    printf("ara(24) = %d\n", ara(24));
    printf("ara(13) = %d\n", ara(13));
    printf("sil(13) = %d\n", sil(13));
    return 0;
}

/* Beklenen cikti:
 * ekle(22) = 0
 * ekle(1) = 1
 * ekle(13) = 2
 * ekle(11) = 3
 * ekle(24) = 4
 * ekle(33) = 5
 * tablo: 22 1 13 11 24 33 . . . . .
 * ara(24) = 4
 * ara(44) = -1
 * sil(13) = 1
 * tablo: 22 1 x 11 24 33 . . . . .
 * ara(24) = 4
 * ara(13) = -1
 * sil(13) = 0
 */
