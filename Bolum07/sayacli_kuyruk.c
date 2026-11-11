/* Sayacli dairesel kuyruk: on ilk ogenin kendisini gosterir, sayac oge
 * sayisidir; boylece KAP hucrenin hepsi kullanilir. Yeni oge
 * (on + sayac) % KAP hucresine yazilir.
 * Notlardaki ornek (Ornek 7.3): KAP = 3; 1, 2, 3, 4 eklenmek istenir
 * (4 reddedilir), bir oge alinir, 4 eklenir (sarma), bir oge daha alinir.
 * Slayt: "Sayacli Kuyruk Adim Adim". */
#include <stdio.h>
#include <stdbool.h>

/* sunumda yok: kapasite (notlardaki ornek) ve kuyruk tipi (notlardan) */
#define KAP 3
typedef struct { int veri[KAP]; int on, sayac; } Kuyruk;

bool ekle(Kuyruk *k, int x) {
  if (k->sayac == KAP) return false;       /* dolu */
  k->veri[(k->on + k->sayac) % KAP] = x;
  k->sayac++;
  return true;
}
bool al(Kuyruk *k, int *x) {
  if (k->sayac == 0) return false;         /* boş */
  *x = k->veri[k->on];
  k->on = (k->on + 1) % KAP;
  k->sayac--;
  return true;
}

/* sunumda yok: durumu ve mantiksal sirayi yazar */
static void durum(const Kuyruk *k) {
  printf("  on = %d, sayac = %d, sira:", k->on, k->sayac);
  for (int i = 0; i < k->sayac; i++) printf(" %d", k->veri[(k->on + i) % KAP]);
  printf("\n");
}

int main(void)
{
  Kuyruk k = { {0}, 0, 0 };
  int x;
  for (int i = 1; i <= 4; i++) {
    printf("ekle %d: %s\n", i, ekle(&k, i) ? "true" : "false (dolu)");
    durum(&k);
  }
  if (al(&k, &x)) printf("al: %d\n", x);
  durum(&k);
  printf("ekle 4: %s\n", ekle(&k, 4) ? "true" : "false (dolu)");
  durum(&k);
  printf("veri[0] = %d (sarma)\n", k.veri[0]);
  if (al(&k, &x)) printf("al: %d\n", x);
  durum(&k);
  return 0;
}

/* Beklenen cikti:
 * ekle 1: true
 *   on = 0, sayac = 1, sira: 1
 * ekle 2: true
 *   on = 0, sayac = 2, sira: 1 2
 * ekle 3: true
 *   on = 0, sayac = 3, sira: 1 2 3
 * ekle 4: false (dolu)
 *   on = 0, sayac = 3, sira: 1 2 3
 * al: 1
 *   on = 1, sayac = 2, sira: 2 3
 * ekle 4: true
 *   on = 1, sayac = 3, sira: 2 3 4
 * veri[0] = 4 (sarma)
 * al: 2
 *   on = 2, sayac = 2, sira: 3 4
 */
