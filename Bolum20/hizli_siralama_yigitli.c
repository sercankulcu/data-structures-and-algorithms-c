/* Ozyinelemesiz hizli siralama (quicksort2): bekleyen (L, R) isleri dizi ile
 * gerceklenen acik bir yigitta tutulur; buyuk parca once itildigi icin hep
 * kucuk parca islenir ve yigit O(lg n) kalir. Ornek, notlardaki
 * [4, 7, 2, 6, 1, 5, 3].
 * Slaytlar: "Ozyinelemesiz Quick Sort" (iki slayt), "quicksort2() Adim Adim". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: makrolar Bolum 19 "Ortak Altyapi: Makrolar" slaytindan */
#define kucuk(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

/* sunumda ikinci slaytta; quicksort2'den once tanimlanmali */
#define YMAX 64     /* > 2·lg n */
static int yigit[YMAX], ust;
void yigit_baslat(void) { ust = 0; }
int yigit_bosmu(void) { return ust == 0; }
void yigit_ekle(int x) { yigit[ust++] = x; }
int yigit_al(void) { return yigit[--ust]; }
#define yigita_at(A, B) \
  do { yigit_ekle(B); yigit_ekle(A); } while (0)

/* sunumda yok: bol "Bolumleme Degismezi" slaytindan */
int bol(int a[], int L, int R) {
    int i = L - 1, j = R, v = a[R]; // pivot a[R]
    for (;;) {
        while (kucuk(a[++i], v))
            ;
        while (kucuk(v, a[--j]))
            if (j == L) break;
        if (i >= j) break;
        SWAP(a[i], a[j]);
    }
    SWAP(a[i], a[R]);
    return i;
}

void quicksort2(int a[], int L, int R) {
  yigit_baslat(); yigita_at(L, R);
  while (!yigit_bosmu()) {
    L = yigit_al(); R = yigit_al();
    if (R <= L) continue;
    int i = bol(a, L, R);
    if (i - L > R - i) {       // büyük parça önce
      yigita_at(L, i - 1); yigita_at(i + 1, R);
    } else {
      yigita_at(i + 1, R); yigita_at(L, i - 1);
    }
  }
}

int main(void) {   /* sunumda yok */
    int a[] = {4, 7, 2, 6, 1, 5, 3};
    quicksort2(a, 0, 6);
    for (int i = 0; i < 7; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti (sonda bosluk var):
 * 1 2 3 4 5 6 7
 */
