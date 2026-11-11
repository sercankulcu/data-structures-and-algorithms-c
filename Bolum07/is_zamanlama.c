/* Round robin is zamanlama benzetimi: surec numaralari bir kuyrukta
 * bekler; ondeki surec en cok Q birim calisir, isi kalirsa sona doner.
 * Kuyruk olarak sayacli dairesel kuyruk kullanilir.
 * Notlardaki ornek: P0 = 5, P1 = 2, P2 = 4 birim is, Q = 2; ayrica
 * notlardaki alistirma Q = 3.
 * Slayt: "Is Zamanlama Benzetimi". */
#include <stdio.h>
#include <stdbool.h>

/* sunumda yok: notlardaki sayacli kuyruk */
#define KAP 16
typedef struct { int veri[KAP]; int on, sayac; } Kuyruk;
bool kuyruk_ekle(Kuyruk *k, int x) {
  if (k->sayac == KAP) return false;
  k->veri[(k->on + k->sayac) % KAP] = x;
  k->sayac++;
  return true;
}
bool kuyruk_al(Kuyruk *k, int *x) {
  if (k->sayac == 0) return false;
  *x = k->veri[k->on];
  k->on = (k->on + 1) % KAP;
  k->sayac--;
  return true;
}

/* sunumda yok: benzetimi verilen Q ile calistirir */
static void benzet(int Q) {
  int kalan[] = {5, 2, 4}; /* P0, P1, P2 iş miktarları */
  int zaman = 0, p;
  Kuyruk k = { {0}, 0, 0 }; /* boş sayaçlı kuyruk */
  for (int i = 0; i < 3; i++)
    kuyruk_ekle(&k, i); /* başta hepsi kuyrukta */
  printf("Q = %d\n", Q);

  /* k: süreç numaraları kuyruğu; Q: zaman dilimi */
  while (kuyruk_al(&k, &p)) {
    int dilim = kalan[p] < Q ? kalan[p] : Q;
    zaman += dilim;
    kalan[p] -= dilim;
    if (kalan[p] > 0)
      kuyruk_ekle(&k, p);           /* sona geri */
    else
      printf("P%d biter: t=%d\n", p, zaman);
  }
}

int main(void)
{
  benzet(2);
  benzet(3);
  return 0;
}

/* Beklenen cikti:
 * Q = 2
 * P1 biter: t=4
 * P2 biter: t=10
 * P0 biter: t=11
 * Q = 3
 * P1 biter: t=5
 * P0 biter: t=10
 * P2 biter: t=11
 */
