/* Dairesel dizide cift uclu kuyruk (deque): basa_ekle on'u bir geri alir
 * ((on - 1 + KAP) % KAP, negatif kalan tuzagi yok), sondan_al son ogeyi
 * (on + sayac - 1) % KAP hucresinden okur.
 * Notlardaki ornek (Ornek 7.4): KAP = 5; sona_ekle ile 10 ve 20 konur,
 * sonra basa_ekle 5, basa_ekle 3 ve iki kez sondan_al; en sonda bastan_al.
 * Slayt: "Deque Adim Adim". */
#include <stdio.h>
#include <stdbool.h>

/* sunumda yok: kapasite (notlardaki ornek) ve deque tipi (notlardan) */
#define KAP 5
typedef struct { int veri[KAP]; int on, sayac; } Deque;

bool basa_ekle(Deque *d, int x) {
  if (d->sayac == KAP) return false;
  d->on = (d->on - 1 + KAP) % KAP;    /* bir geri */
  d->veri[d->on] = x;  d->sayac++;
  return true;
}
bool sondan_al(Deque *d, int *x) {
  if (d->sayac == 0) return false;
  *x = d->veri[(d->on + d->sayac - 1) % KAP];
  d->sayac--;  return true;
}

/* sunumda yok: notlardaki sona_ekle ve bastan_al */
bool sona_ekle(Deque *d, int x) {
  if (d->sayac == KAP) return false;
  d->veri[(d->on + d->sayac) % KAP] = x; /* son öğenin bir sonrası */
  d->sayac++;
  return true;
}
bool bastan_al(Deque *d, int *x) {
  if (d->sayac == 0) return false;
  *x = d->veri[d->on];
  d->on = (d->on + 1) % KAP;             /* bir ileri */
  d->sayac--;
  return true;
}

/* sunumda yok: on, sayac ve mantiksal sirayi yazar */
static void durum(const char *islem, const Deque *d) {
  printf("%s: on = %d, sayac = %d, sira:", islem, d->on, d->sayac);
  for (int i = 0; i < d->sayac; i++) printf(" %d", d->veri[(d->on + i) % KAP]);
  printf("\n");
}

int main(void)
{
  Deque d = { {0}, 0, 0 };
  int x;
  sona_ekle(&d, 10);
  sona_ekle(&d, 20);
  durum("baslangic", &d);
  basa_ekle(&d, 5);
  durum("basa_ekle 5", &d);
  basa_ekle(&d, 3);
  durum("basa_ekle 3", &d);
  sondan_al(&d, &x);
  printf("sondan_al -> %d\n", x);
  durum("sondan_al", &d);
  sondan_al(&d, &x);
  printf("sondan_al -> %d\n", x);
  durum("sondan_al", &d);
  bastan_al(&d, &x);
  printf("bastan_al -> %d\n", x);
  durum("bastan_al", &d);
  return 0;
}

/* Beklenen cikti:
 * baslangic: on = 0, sayac = 2, sira: 10 20
 * basa_ekle 5: on = 4, sayac = 3, sira: 5 10 20
 * basa_ekle 3: on = 3, sayac = 4, sira: 3 5 10 20
 * sondan_al -> 20
 * sondan_al: on = 3, sayac = 3, sira: 3 5 10
 * sondan_al -> 10
 * sondan_al: on = 3, sayac = 2, sira: 3 5
 * bastan_al -> 3
 * bastan_al: on = 4, sayac = 1, sira: 5
 */
