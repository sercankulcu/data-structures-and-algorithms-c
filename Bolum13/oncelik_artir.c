/* Onceligi degisen oge: maksimum heap'te onceligi artan oge ebeveyninden
 * buyuk oldugu surece yukari kaydirilir (sunum); onceligi azalan oge
 * asagi kaydirilir (ders notundaki oncelik_azalt).
 * Notlardaki ornek (Ornek 13.3): 30, 15, 28, 11, 14, 3, 6, 10, 9 heap'inde
 * oncelik_artir(9, 31) ve ayni baslangicta oncelik_azalt(1, 5).
 * Slayt: "Problemi iyi yakalamak". */
#include <stdio.h>

/* sunumda yok: "C tanimlari" slaytindaki tanimlar */
#define ELEMAN_SAYISI 200   /* maksimum öğe + 1 */

typedef struct {
  int x;          /* öncelik (anahtar) */
  /* diğer alanlar */
} eleman;

eleman yigin[ELEMAN_SAYISI];  /* [0] kullanılmaz */
int n = 0;                    /* öğe sayısı */

/* k konumundaki öğenin önceliği arttı: yukarı kaydır */
void oncelik_artir(int k, int yeni) {
  eleman e = yigin[k];
  e.x = yeni;
  while (k != 1 && e.x > yigin[k / 2].x) {
    yigin[k] = yigin[k / 2];
    k /= 2;
  }
  yigin[k] = e;
}

/* sunumda yok: ders notundaki asagi kaydirma surumu */
/* k konumundaki öğenin önceliği azaldı: aşağı kaydır */
void oncelik_azalt(int k, int yeni) {
  eleman e = yigin[k];
  e.x = yeni;
  int j = 2 * k;
  while (j <= n) {
    if (j < n && yigin[j].x < yigin[j + 1].x) j++;
    if (e.x >= yigin[j].x) break;
    yigin[k] = yigin[j];
    k = j; j *= 2;
  }
  yigin[k] = e;
}

/* sunumda yok: heap'i verilen degerlerle doldurur */
static void doldur(const int a[], int m) {
    for (int i = 0; i < m; i++)
        yigin[i + 1].x = a[i];
    n = m;
}

/* sunumda yok: yigin[1..n]'yi yazar */
static void yazdir(void) {
    for (int i = 1; i <= n; i++)
        printf(i == 1 ? "%d" : ", %d", yigin[i].x);
    printf("\n");
}

int main(void)
{
    int a[] = {30, 15, 28, 11, 14, 3, 6, 10, 9};
    doldur(a, 9);
    printf("baslangic:              ");
    yazdir();
    oncelik_artir(9, 31);
    printf("oncelik_artir(9, 31):   ");
    yazdir();

    doldur(a, 9);
    oncelik_azalt(1, 5);
    printf("oncelik_azalt(1, 5):    ");
    yazdir();
    return 0;
}

/* Beklenen cikti:
 * baslangic:              30, 15, 28, 11, 14, 3, 6, 10, 9
 * oncelik_artir(9, 31):   31, 30, 28, 15, 14, 3, 6, 10, 11
 * oncelik_azalt(1, 5):    28, 15, 6, 11, 14, 3, 5, 10, 9
 */
