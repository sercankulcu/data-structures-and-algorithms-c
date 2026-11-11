/* Dizide maksimum heap: yigin[1..n], i'nin ebeveyni i/2, cocuklari 2i ve
 * 2i+1. Ekleme boslugu yukari, alma sondaki ogeyi asagi kaydirir.
 * Notlardaki ornekler: 14, 12, 7, 10, 8, 6 heap'ine 15, 109, 107, 3, 15
 * eklenir ve iki kez alinir (Ornek 13.4); 30, 15, 28, 11, 14, 3, 6, 10, 9
 * heap'i bosalana dek alinir (Tablo 13.6-13.8).
 * Slaytlar: "C tanimlari", "Ekleme yordami", "Izleme: ekle(15)",
 * "Izleme: ekle(109)", "Silme yordami", "Izleme: al() - 1", "Izleme: al() - 2". */
#include <stdio.h>
#include <stdbool.h>

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

void maksimum_yigin_ekle(eleman item) {
  if (YIGIN_DOLUMU(n)) {
    yigin_dolu();             /* hata iletisi */
    return;
  }
  int i = ++n;
  while (i != 1) {            /* i == 1: kökteyiz */
    if (item.x <= yigin[i / 2].x) break;
    yigin[i] = yigin[i / 2];  /* ebeveyni aşağı kaydır */
    i /= 2;                   /* bir üst ebeveyne bak */
  }
  yigin[i] = item;
}

bool maksimum_yigin_al(eleman *cikan) {
  if (YIGIN_BOSMU(n)) return false;
  *cikan = yigin[1];          /* kök döndürülecek */
  eleman deger = yigin[n--];  /* yeri aranacak */
  int i = 1, j = 2;
  while (j <= n) {
    if (j < n && yigin[j].x < yigin[j + 1].x) j++;
    if (deger.x >= yigin[j].x) break;
    yigin[i] = yigin[j];      /* çocuğu yukarı al */
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
    int ilk[] = {14, 12, 7, 10, 8, 6};
    for (int i = 0; i < 6; i++) {
        eleman e = {ilk[i]};
        maksimum_yigin_ekle(e);
    }
    printf("baslangic: ");
    yazdir();

    int yeni[] = {15, 109, 107, 3, 15};
    for (int i = 0; i < 5; i++) {
        eleman e = {yeni[i]};
        maksimum_yigin_ekle(e);
        printf("+%d: ", yeni[i]);
        yazdir();
    }
    eleman cikan;
    for (int i = 0; i < 2; i++) {
        maksimum_yigin_al(&cikan);
        printf("al %d: ", cikan.x);
        yazdir();
    }

    n = 0;                    /* ikinci ornek: heap'i bastan kur */
    int ikinci[] = {30, 15, 28, 11, 14, 3, 6, 10, 9};
    for (int i = 0; i < 9; i++) {
        eleman e = {ikinci[i]};
        maksimum_yigin_ekle(e);
    }
    printf("baslangic: ");
    yazdir();
    while (maksimum_yigin_al(&cikan)) {
        printf("al %d: ", cikan.x);
        yazdir();
    }
    printf("bos heap'ten al: %s\n",
           maksimum_yigin_al(&cikan) ? "true" : "false");
    return 0;
}

/* Beklenen cikti:
 * baslangic: 14, 12, 7, 10, 8, 6
 * +15: 15, 12, 14, 10, 8, 6, 7
 * +109: 109, 15, 14, 12, 8, 6, 7, 10
 * +107: 109, 107, 14, 15, 8, 6, 7, 10, 12
 * +3: 109, 107, 14, 15, 8, 6, 7, 10, 12, 3
 * +15: 109, 107, 14, 15, 15, 6, 7, 10, 12, 3, 8
 * al 109: 107, 15, 14, 12, 15, 6, 7, 10, 8, 3
 * al 107: 15, 15, 14, 12, 3, 6, 7, 10, 8
 * baslangic: 30, 15, 28, 11, 14, 3, 6, 10, 9
 * al 30: 28, 15, 9, 11, 14, 3, 6, 10
 * al 28: 15, 14, 9, 11, 10, 3, 6
 * al 15: 14, 11, 9, 6, 10, 3
 * al 14: 11, 10, 9, 6, 3
 * al 11: 10, 6, 9, 3
 * al 10: 9, 6, 3
 * al 9: 6, 3
 * al 6: 3
 * al 3: (bos)
 * bos heap'ten al: false
 */
