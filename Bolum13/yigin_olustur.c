/* Global dizi yerine yapi: Yigin dizinin adresini, oge sayisini ve
 * kapasiteyi tutar; dizi calisma sirasinda ayrilir, iki ayirma da denetlenir.
 * Ekleme ve alma sunumda yok; ders notundaki yigin_ekle / yigin_al
 * kullanilir (basari true/false ile bildirilir).
 * Notlardaki ornek: yigin_olustur(4), 20, 5, 30, 10, 40 eklenmeye calisilir
 * (besincisi dolu oldugu icin false), sonra bosalana dek alinir.
 * Slayt: "Daha iyi bir arayuz". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* sunumda yok: "C tanimlari" slaytindaki oge tipi */
typedef struct {
  int x;          /* öncelik (anahtar) */
  /* diğer alanlar */
} eleman;

typedef struct { eleman *a; int n, kapasite; } Yigin;

Yigin *yigin_olustur(int kapasite) {
  Yigin *h = malloc(sizeof *h);
  if (h == NULL) return NULL;
  h->a = malloc((kapasite + 1) * sizeof *h->a);
  if (h->a == NULL) { free(h); return NULL; }
  h->n = 0; h->kapasite = kapasite;
  return h;
}
void yigin_yok_et(Yigin *h) { if (h) { free(h->a); free(h); } }

/* sunumda yok: yapi surumunun ekleme ve almasi (ders notundan) */
bool yigin_ekle(Yigin *h, eleman item) {
  if (h->n == h->kapasite) return false;   /* dolu */
  int i = ++h->n;
  while (i != 1 && item.x > h->a[i / 2].x) {
    h->a[i] = h->a[i / 2];
    i /= 2;
  }
  h->a[i] = item;
  return true;
}
bool yigin_al(Yigin *h, eleman *cikan) {
  if (h->n == 0) return false;             /* boş */
  *cikan = h->a[1];
  eleman deger = h->a[h->n--];
  int i = 1, j = 2;
  while (j <= h->n) {
    if (j < h->n && h->a[j].x < h->a[j + 1].x) j++;
    if (deger.x >= h->a[j].x) break;
    h->a[i] = h->a[j];
    i = j; j *= 2;
  }
  h->a[i] = deger;
  return true;
}

int main(void)
{
    Yigin *h = yigin_olustur(4);
    if (h == NULL) return 1;
    printf("kapasite = %d, n = %d\n", h->kapasite, h->n);
    int a[] = {20, 5, 30, 10, 40};
    for (int i = 0; i < 5; i++) {
        eleman e = {a[i]};
        printf("yigin_ekle(%d) = %s\n", a[i],
               yigin_ekle(h, e) ? "true" : "false");
    }
    eleman cikan;
    printf("alinanlar:");
    while (yigin_al(h, &cikan))
        printf(" %d", cikan.x);
    printf("\n");
    yigin_yok_et(h);
    yigin_yok_et(NULL);       /* zararsiz */
    return 0;
}

/* Beklenen cikti:
 * kapasite = 4, n = 0
 * yigin_ekle(20) = true
 * yigin_ekle(5) = true
 * yigin_ekle(30) = true
 * yigin_ekle(10) = true
 * yigin_ekle(40) = false
 * alinanlar: 30 20 10 5
 */
