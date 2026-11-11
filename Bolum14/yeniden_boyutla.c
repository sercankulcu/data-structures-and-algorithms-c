/* Yeniden boyutlandirma: dinamik tabloya her eklemeden sonra yuk faktoru
 * denetlenir; alfa > 1/2 olunca tablo, iki katindan kucuk olmayan ilk asal
 * boyuta buyutulur ve her DOLU oge yeni tabloya yeniden hash'lenir.
 * Notlardaki ornek (Tablo 14.16): 5 yuvali tabloya 7, 12, 3 eklenir; 3'ten
 * sonra alfa = 0,6 olur ve tablo 11 yuvaya buyur (12 -> 1, 3 -> 3, 7 -> 7).
 * Slaytlar: "Yeniden boyutlandirma", "Izleme: yeniden_boyutla". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* sunumda yok: "Acik adresleme: C" slaytindaki yuva tipi */
typedef enum { BOS, DOLU, SILINDI } durum_t;
typedef struct {
  int anahtar;          /* anahtar >= 0 varsayılır */
  durum_t durum;
} yuva;

typedef struct {
  yuva *a;      /* m yuvalık dinamik dizi */
  int m, n;     /* boyut, dolu yuva sayısı */
} Tablo;

/* sunumda yok: iki yardimci (ders notundaki surumler) */
int sonraki_asal(int x) {   /* x'ten küçük olmayan ilk asal */
  for (;; x++) {
    int asal = x >= 2;
    for (int d = 2; d * d <= x && asal; d++)
      if (x % d == 0) asal = 0;
    if (asal) return x;
  }
}
int tablo_ekle(Tablo *t, int k) {   /* doğrusal yoklama, m = t->m */
  int i = k % t->m;
  for (int d = 0; d < t->m; d++, i = (i + 1) % t->m) {
    if (t->a[i].durum != DOLU) {
      t->a[i].anahtar = k;
      t->a[i].durum = DOLU;
      t->n++;
      return i;
    }
  }
  return -1;
}

bool yeniden_boyutla(Tablo *t, int yeni_m) {
  yuva *eski = t->a;
  int eski_m = t->m;
  yuva *a = calloc(yeni_m, sizeof *a);  /* BOS */
  if (a == NULL) return false;
  t->a = a; t->m = yeni_m; t->n = 0;
  for (int i = 0; i < eski_m; i++)
    if (eski[i].durum == DOLU)
      tablo_ekle(t, eski[i].anahtar);
  free(eski);
  return true;
}

/* sunumda yok: tabloyu yazar; bos yuva "." */
static void yazdir(const Tablo *t) {
    printf("m = %d, n = %d:", t->m, t->n);
    for (int i = 0; i < t->m; i++) {
        if (t->a[i].durum == DOLU) printf(" %d", t->a[i].anahtar);
        else printf(" .");
    }
    printf("\n");
}

int main(void)
{
    Tablo tablo = {NULL, 5, 0}, *t = &tablo;
    t->a = calloc(t->m, sizeof *t->a);    /* sunumda yok: ilk dizi */
    if (t->a == NULL) return 1;
    int k[] = {7, 12, 3};
    for (int i = 0; i < 3; i++) {
        tablo_ekle(t, k[i]);
        printf("+%d: ", k[i]);
        yazdir(t);
/* ekledikten sonra: */
if (2 * t->n > t->m)             /* α > 1/2 */
  yeniden_boyutla(t, sonraki_asal(2 * t->m));
    }
    printf("son: ");
    yazdir(t);
    free(t->a);
    return 0;
}

/* Beklenen cikti:
 * +7: m = 5, n = 1: . . 7 . .
 * +12: m = 5, n = 2: . . 7 12 .
 * +3: m = 5, n = 3: . . 7 12 3
 * son: m = 11, n = 3: . 12 . 3 . . . 7 . . .
 */
