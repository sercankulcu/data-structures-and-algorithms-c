/* Bagli liste ile kuyruk: ekleme arkaya, cikarma onden yapilir; ikisi de
 * O(1). Bos kuyruga ilk eklemede on da degisir; son oge cikinca arka da
 * NULL yapilir (yoksa sarkan isaretci kalir).
 * Notlardaki ornekler: bos kuyruga 10, 20, 30 eklenir; 10 -> 20
 * kuyrugundan uc kez kuyruk_al (ucuncusu false).
 * Slaytlar: "Bagli kuyruk_ekle Adim Adim", "Bagli kuyruk_al Adim Adim". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* sunumda yok: dugum tipi (notlardan) */
typedef struct dugum { int deger; struct dugum *bag; } dugum;

bool kuyruk_ekle(dugum **on, dugum **arka, int x) {
  dugum *yeni = malloc(sizeof *yeni);
  if (yeni == NULL) return false;
  yeni->deger = x;  yeni->bag = NULL;
  if (*arka == NULL) *on = yeni;   /* boş kuyruk */
  else (*arka)->bag = yeni;        /* sona bağla */
  *arka = yeni;
  return true;
}

bool kuyruk_al(dugum **on, dugum **arka, int *x) {
  dugum *eski = *on;
  if (eski == NULL) return false;      /* boş */
  *x = eski->deger;
  *on = eski->bag;
  if (*on == NULL) *arka = NULL;  /* son öğe gitti */
  free(eski);
  return true;
}

/* sunumda yok: kuyrugu ondan arkaya yazar */
static void yaz(const dugum *on, const dugum *arka) {
  printf("kuyruk:");
  for (; on != NULL; on = on->bag) printf(" %d", on->deger);
  if (arka != NULL) printf(" (arka = %d)\n", arka->deger);
  else printf(" (arka = NULL)\n");
}

int main(void)
{
  dugum *on = NULL, *arka = NULL;
  int x;
  kuyruk_ekle(&on, &arka, 10);
  yaz(on, arka);
  kuyruk_ekle(&on, &arka, 20);
  kuyruk_ekle(&on, &arka, 30);
  yaz(on, arka);
  kuyruk_al(&on, &arka, &x);
  printf("kuyruk_al: %d\n", x);
  yaz(on, arka);

  /* kalan 20 -> 30 kuyrugundan uc kez al; ikinci alma son ogeyi alir */
  for (int i = 0; i < 3; i++) {
    if (kuyruk_al(&on, &arka, &x)) printf("kuyruk_al: true, %d\n", x);
    else printf("kuyruk_al: false (bos)\n");
    yaz(on, arka);
  }
  kuyruk_ekle(&on, &arka, 40);          /* bosalmis kuyruga yeniden ekleme */
  yaz(on, arka);
  kuyruk_al(&on, &arka, &x);            /* sunumda yok: bellegi iade et */
  return 0;
}

/* Beklenen cikti:
 * kuyruk: 10 (arka = 10)
 * kuyruk: 10 20 30 (arka = 30)
 * kuyruk_al: 10
 * kuyruk: 20 30 (arka = 30)
 * kuyruk_al: true, 20
 * kuyruk: 30 (arka = 30)
 * kuyruk_al: true, 30
 * kuyruk: (arka = NULL)
 * kuyruk_al: false (bos)
 * kuyruk: (arka = NULL)
 * kuyruk: 40 (arka = 40)
 */
