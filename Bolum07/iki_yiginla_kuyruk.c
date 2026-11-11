/* Iki yiginla kuyruk: ekle her zaman giris yiginina iter; al, cikis
 * yigini bossa giristeki her seyi cikisa aktarir (sira iki kez ters
 * cevrilmis olur) ve cikistan alir.
 * Notlardaki ornek: ekle 1, 2, 3; al; ekle 4; uc kez al; bos kuyruktan al.
 * Slayt: "Iki Yiginla Kuyruk". */
#include <stdio.h>
#include <stdbool.h>

/* sunumda yok: Bolum 6'daki struct yigini ve Kuyruk2 tipi (notlardan) */
#define KAP 100
typedef struct {
    int veri[KAP];
    int ust;               /* boşken -1 */
} Yigit;
bool yigit_bos(const Yigit *y) { return y->ust < 0; }
bool push(Yigit *y, int x) {
  if (y->ust == KAP - 1) return false;
  y->veri[++y->ust] = x;
  return true;
}
bool pop(Yigit *y, int *x) {
  if (y->ust < 0) return false;
  *x = y->veri[y->ust--];
  return true;
}
typedef struct { Yigit giris, cikis; } Kuyruk2;

void ekle(Kuyruk2 *q, int x) {
  push(&q->giris, x);
}
bool al(Kuyruk2 *q, int *x) {
  int t;
  if (yigit_bos(&q->cikis))       /* çıkış boşsa */
    while (pop(&q->giris, &t))    /* hepsini aktar */
      push(&q->cikis, t);
  return pop(&q->cikis, x);
}

/* sunumda yok: bir alma yapar, sonucu ve yiginlarin boyunu yazar */
static void al_yaz(Kuyruk2 *q) {
  int x;
  if (al(q, &x)) printf("al -> %d", x);
  else printf("al -> false (bos)");
  printf("  giris %d oge, cikis %d oge\n", q->giris.ust + 1, q->cikis.ust + 1);
}

int main(void)
{
  Kuyruk2 q;
  q.giris.ust = -1;
  q.cikis.ust = -1;
  ekle(&q, 1);
  ekle(&q, 2);
  ekle(&q, 3);
  al_yaz(&q);              /* 3, 2, 1 aktarilir */
  ekle(&q, 4);
  al_yaz(&q);              /* aktarma yok */
  al_yaz(&q);
  al_yaz(&q);              /* 4 aktarilir */
  al_yaz(&q);
  return 0;
}

/* Beklenen cikti:
 * al -> 1  giris 0 oge, cikis 2 oge
 * al -> 2  giris 1 oge, cikis 1 oge
 * al -> 3  giris 1 oge, cikis 0 oge
 * al -> 4  giris 0 oge, cikis 0 oge
 * al -> false (bos)  giris 0 oge, cikis 0 oge
 */
