/* Tek bellek dizisinde n yigin: yigin i bellek[sinir[i]+1 .. sinir[i+1]]
 * kesimini kullanir; bos: top[i] == sinir[i], dolu: top[i] == sinir[i+1].
 * Notlardaki ornek: m = 12, n = 3, top = sinir = [-1, 3, 7], sinir[3] = 11.
 * Yedinci cagri ekle(0, 6) reddedilir, oysa bellekte alti hucre bostur.
 * Slayt: "Coklu Yigin Adim Adim". */
#include <stdio.h>
#include <stdbool.h>

/* sunumda yok: kuresel bellek, top ve sinir dizileri */
#define M 12                 /* bellek boyu */
#define N 3                  /* yigin sayisi */
int bellek[M];
int top[N];
int sinir[N + 1];

/* yığın i: bellek[sinir[i]+1 .. sinir[i+1]] */
bool ekle(int i, int x) {
  if (top[i] == sinir[i + 1]) return false; /* dolu */
  bellek[++top[i]] = x;
  return true;
}
bool al(int i, int *x) {
  if (top[i] == sinir[i]) return false;     /* boş */
  *x = bellek[top[i]--];
  return true;
}

/* sunumda yok: top dizisini yazar */
static void yaz_top(void) {
  printf("top = [%d, %d, %d]\n", top[0], top[1], top[2]);
}

int main(void)
{
  int i, x;
  int yigin[] = {0, 1, 0, 2, 0, 0, 0};
  int deger[] = {5, 7, 9, 4, 2, 8, 6};
  for (i = 0; i < N; i++)                 /* esit kesimler, hepsi bos */
    top[i] = sinir[i] = (M / N) * i - 1;
  sinir[N] = M - 1;
  printf("sinir = [%d, %d, %d, %d], ", sinir[0], sinir[1], sinir[2], sinir[3]);
  yaz_top();
  for (i = 0; i < 7; i++) {
    bool ok = ekle(yigin[i], deger[i]);
    printf("ekle(%d, %d): %-5s ", yigin[i], deger[i], ok ? "true" : "false");
    yaz_top();
  }
  if (al(1, &x)) printf("al(1, &x): true, x = %d ", x);
  yaz_top();
  printf("al(1, &x) yine: %s\n", al(1, &x) ? "true" : "false");
  return 0;
}

/* Not: "true" sonrasinda iki, "false" sonrasinda bir bosluk. */
/* Beklenen cikti:
 * sinir = [-1, 3, 7, 11], top = [-1, 3, 7]
 * ekle(0, 5): true  top = [0, 3, 7]
 * ekle(1, 7): true  top = [0, 4, 7]
 * ekle(0, 9): true  top = [1, 4, 7]
 * ekle(2, 4): true  top = [1, 4, 8]
 * ekle(0, 2): true  top = [2, 4, 8]
 * ekle(0, 8): true  top = [3, 4, 8]
 * ekle(0, 6): false top = [3, 4, 8]
 * al(1, &x): true, x = 7 top = [3, 3, 8]
 * al(1, &x) yine: false
 */
