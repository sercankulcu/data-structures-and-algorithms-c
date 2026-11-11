/* Minimum heap: maksimum heap yordamlarinda yalniz karsilastirmalarin
 * yonu degisir. Ekleme sunumdan, alma ders notundan (13.5.2).
 * Notlardaki ornek: bos heap'e 20, 5, 30, 10, 40 eklenir, sonra bosalana
 * dek alinir; ogeler artan sirada cikar.
 * Slayt: "Minimum heap". */
#include <stdio.h>
#include <stdbool.h>

/* sunumda yok: "C tanimlari" slaytindaki tanimlar */
#define ELEMAN_SAYISI 200   /* maksimum öğe + 1 */
#define YIGIN_DOLUMU(n) ((n) == ELEMAN_SAYISI - 1)
#define YIGIN_BOSMU(n)  (!(n))

typedef struct {
  int x;          /* öncelik (anahtar) */
  /* diğer alanlar */
} eleman;

eleman yigin[ELEMAN_SAYISI];  /* [0] kullanılmaz */
int n = 0;                    /* öğe sayısı */

/* sunumda yok: dolu heap icin hata iletisi */
void yigin_dolu(void) {
    fprintf(stderr, "Yigin dolu\n");
}

void minimum_yigin_ekle(eleman item) {
  /* ... dolu denetimi aynı ... */
  if (YIGIN_DOLUMU(n)) {      /* sunumda yok: atlanan dolu denetimi */
    yigin_dolu();
    return;
  }
  int i = ++n;
  while (i != 1) {
    if (item.x >= yigin[i / 2].x) break; /* >= ! */
    yigin[i] = yigin[i / 2];
    i /= 2;
  }
  yigin[i] = item;
}

/* sunumda yok: minimum heap'ten alma (ders notundaki surum) */
bool minimum_yigin_al(eleman *cikan) {
  if (YIGIN_BOSMU(n)) return false;
  *cikan = yigin[1];
  eleman deger = yigin[n--];
  int i = 1, j = 2;
  while (j <= n) {
    if (j < n && yigin[j].x > yigin[j + 1].x) j++;  /* küçük çocuk */
    if (deger.x <= yigin[j].x) break;               /* <= ! */
    yigin[i] = yigin[j];
    i = j; j *= 2;
  }
  yigin[i] = deger;
  return true;
}

/* sunumda yok: yigin[1..n]'yi yazar */
static void yazdir(void) {
    if (n == 0) printf("(bos)");
    for (int i = 1; i <= n; i++)
        printf(i == 1 ? "%d" : ", %d", yigin[i].x);
    printf("\n");
}

int main(void)
{
    int a[] = {20, 5, 30, 10, 40};
    for (int i = 0; i < 5; i++) {
        eleman e = {a[i]};
        minimum_yigin_ekle(e);
        printf("+%d: ", a[i]);
        yazdir();
    }
    eleman cikan;
    while (minimum_yigin_al(&cikan)) {
        printf("al %d: ", cikan.x);
        yazdir();
    }
    return 0;
}

/* Beklenen cikti:
 * +20: 20
 * +5: 5, 20
 * +30: 5, 20, 30
 * +10: 5, 10, 30, 20
 * +40: 5, 10, 30, 20, 40
 * al 5: 10, 20, 30, 40
 * al 10: 20, 40, 30
 * al 20: 30, 40
 * al 30: 40
 * al 40: (bos)
 */
