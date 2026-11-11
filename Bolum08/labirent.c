/* Labirentte yigitla geri izleme: izbul yordami 8x8'lik labirentte giris
 * (1,1)'den cikis (6,6)'ya yol arar ve bulunan yolu yazar. Ikinci surum
 * (izbul_kisa) ayni dongunun kisaltilmis yazimidir (ys/yy adlari ve
 * bilesik degismez); iki surum ayni yolu bulur.
 * Slaytlar: "Labirent: Veri Yapilari", "izbul Yordami", "Labirent Adim Adim". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: exit, EXIT_FAILURE */

#define FALSE 0       /* sunumda yok */
#define TRUE 1        /* sunumda yok */

#define MAX_STACK_SIZE 100
#define CIKIS_SATIR 6
#define CIKIS_SUTUN 6
typedef struct { short int dikey, yatay; } yonler;
yonler hareket[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1},
                     {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
typedef struct { short int satir, sutun, yon; } element;
element yigit[MAX_STACK_SIZE];
int top = -1;
short int gezildi[8][8];
short int labirent[8][8] = {{1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,1}, {1,0,1,0,1,1,1,1},
    {1,1,0,1,1,1,1,1}, {1,0,1,1,0,1,1,1},
    {1,1,0,0,1,0,1,1}, {1,1,1,1,1,1,0,1},
    {1,1,1,1,1,1,1,1}};

/* sunumda yok: yigin islemleri (top adresle verilir) */
void yigit_ekle(int *top, element oge)
{
    if (*top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Yigit dolu\n");
        exit(EXIT_FAILURE);
    }
    yigit[++*top] = oge;
}

element yigit_al(int *top)
{
    if (*top == -1) {
        fprintf(stderr, "Yigit bos\n");
        exit(EXIT_FAILURE);
    }
    return yigit[(*top)--];
}

void izbul(void) {
  short int satir, sutun, y_satir, y_sutun;
  int i, yon, bulundu = FALSE;
  element konum;
  yigit[0].satir = yigit[0].sutun = 1;
  yigit[0].yon = 1;     /* ilk konum yığına */
  gezildi[1][1] = 1;  top = 0;
  satir = sutun = 0;  /* sunumda yok: "may be used uninitialized" uyarisina karsi */
  while (top > -1 && !bulundu) {
    konum = yigit_al(&top);   /* yeni konum */
    satir = konum.satir;
    sutun = konum.sutun;
    yon = konum.yon;          /* hangi yöne */
    while (yon < 8 && !bulundu) {
      y_satir = satir + hareket[yon].dikey;
      y_sutun = sutun + hareket[yon].yatay;
      if (y_satir == CIKIS_SATIR &&
          y_sutun == CIKIS_SUTUN)
        bulundu = TRUE;       /* çıkış mı? */
      else if (!labirent[y_satir][y_sutun] &&
               !gezildi[y_satir][y_sutun]) {
        gezildi[y_satir][y_sutun] = 1;
        konum.satir = satir;  /* nereden */
        konum.sutun = sutun;
        konum.yon = ++yon;    /* dönüşte yön */
        yigit_ekle(&top, konum);
        satir = y_satir;  sutun = y_sutun;
        yon = 0;
      } else ++yon;           /* başka yön */
    }                         /* geri adım */
  }
  /* sunumda yok: yolu yazan son kisim (ders notundaki gibi) */
  if (bulundu) {
    printf("satir sutun\n");
    for (i = 0; i <= top; i++)        /* yığındaki yol */
      printf("%2d%5d\n", yigit[i].satir, yigit[i].sutun);
    printf("%2d%5d\n", satir, sutun);      /* son konum */
    printf("%2d%5d\n", CIKIS_SATIR, CIKIS_SUTUN);
  } else printf("Cikis yolu bulunamadi!\n");
}

/* sunumda yok: "Labirent Adim Adim" slaytindaki dongu bu fonksiyonun
 * govdesidir; bildirimler, baslangic ve yazdirma izbul'dakiyle aynidir. */
void izbul_kisa(void) {
  short int satir = 0, sutun = 0, ys, yy;
  int i, j, yon, bulundu = FALSE;
  element konum;
  for (i = 0; i < 8; i++)             /* gezildi'yi sifirla */
    for (j = 0; j < 8; j++)
      gezildi[i][j] = 0;
  yigit[0].satir = yigit[0].sutun = 1;
  yigit[0].yon = 1;
  gezildi[1][1] = 1;  top = 0;
  /* slayt kodu: */
while (top > -1 && !bulundu) {
  konum = yigit_al(&top);
  satir = konum.satir;  sutun = konum.sutun;
  yon = konum.yon;
  while (yon < 8 && !bulundu) {
    ys = satir + hareket[yon].dikey;
    yy = sutun + hareket[yon].yatay;
    if (ys == CIKIS_SATIR && yy == CIKIS_SUTUN)
      bulundu = TRUE;
    else if (!labirent[ys][yy] &&
             !gezildi[ys][yy]) {
      gezildi[ys][yy] = 1;
      konum = (element){satir, sutun, ++yon};
      yigit_ekle(&top, konum);
      satir = ys;  sutun = yy;  yon = 0;
    } else ++yon;
} }
  /* slayt kodu sonu */
  if (bulundu) {
    printf("satir sutun\n");
    for (i = 0; i <= top; i++)
      printf("%2d%5d\n", yigit[i].satir, yigit[i].sutun);
    printf("%2d%5d\n", satir, sutun);
    printf("%2d%5d\n", CIKIS_SATIR, CIKIS_SUTUN);
  } else printf("Cikis yolu bulunamadi!\n");
}

int main(void)
{
    printf("izbul:\n");
    izbul();
    printf("izbul_kisa:\n");
    izbul_kisa();
    return 0;
}

/* Beklenen cikti:
 * izbul:
 * satir sutun
 *  1    1
 *  2    1
 *  3    2
 *  4    1
 *  5    2
 *  5    3
 *  4    4
 *  5    5
 *  6    6
 * izbul_kisa:
 * satir sutun
 *  1    1
 *  2    1
 *  3    2
 *  4    1
 *  5    2
 *  5    3
 *  4    4
 *  5    5
 *  6    6
 */
