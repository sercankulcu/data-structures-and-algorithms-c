/* Dairesel kuyrugun guvenli surumu: yeni arka once yerel degiskende
 * hesaplanir; kuyruk doluysa arka degismeden false doner, bossa false
 * doner. Programi bitirmez.
 * Notlardaki ornek (Ornek 7.2): bes hucre, on = arka = 0; A..E eklenmek
 * istenir (E reddedilir), iki oge alinir, sonra E, F, G (G reddedilir).
 * Slayt: "Dairesel Kuyruk Adim Adim". */
#include <stdio.h>
#include <stdbool.h>

/* sunumda yok: boyut (notlardaki ornek) ve oge tipi */
#define MAX_QUEUE_SIZE 5
typedef struct {
    int deger;
} element;
element kuyruk[MAX_QUEUE_SIZE];

bool kuyruk_ekle(int on, int *arka, element x) {
  int yeni = (*arka + 1) % MAX_QUEUE_SIZE;
  if (yeni == on) return false;       /* dolu */
  *arka = yeni;  kuyruk[yeni] = x;
  return true;
}
bool kuyruk_al(int *on, int arka, element *x) {
  if (*on == arka) return false;      /* boş */
  *on = (*on + 1) % MAX_QUEUE_SIZE;
  *x = kuyruk[*on];  return true;
}

/* sunumda yok: bir ekleme yapar ve sonucu yazar */
static void ekle(int on, int *arka, char c) {
  element e;
  bool ok;
  e.deger = c;
  ok = kuyruk_ekle(on, arka, e);
  printf("ekle %c: %s, on = %d, arka = %d\n", c, ok ? "true" : "false (dolu)",
         on, *arka);
}

int main(void)
{
  int on = 0, arka = 0;
  element e;
  const char *harf = "ABCDE";
  for (int i = 0; i < 5; i++) ekle(on, &arka, harf[i]);
  for (int i = 0; i < 2; i++)
    if (kuyruk_al(&on, arka, &e))
      printf("al: true, %c, on = %d, arka = %d\n", e.deger, on, arka);
  ekle(on, &arka, 'E');
  ekle(on, &arka, 'F');
  ekle(on, &arka, 'G');
  while (kuyruk_al(&on, arka, &e))       /* sunumda yok: kalanlari al */
    printf("al: %c\n", e.deger);
  printf("al: false (bos)\n");
  return 0;
}

/* Beklenen cikti:
 * ekle A: true, on = 0, arka = 1
 * ekle B: true, on = 0, arka = 2
 * ekle C: true, on = 0, arka = 3
 * ekle D: true, on = 0, arka = 4
 * ekle E: false (dolu), on = 0, arka = 4
 * al: true, A, on = 1, arka = 4
 * al: true, B, on = 2, arka = 4
 * ekle E: true, on = 2, arka = 0
 * ekle F: true, on = 2, arka = 1
 * ekle G: false (dolu), on = 2, arka = 1
 * al: C
 * al: D
 * al: E
 * al: F
 * al: false (bos)
 */
