/* Dijkstra (EnKisaYolBul): her turda en yakin isaretsiz dugum (minimumBul)
 * kesinlesir ve komsulari gevsetilir; onceki[] en kisa yol agacini tutar,
 * yol_yaz yolu ozyinelemeyle kaynaktan hedefe yazar. Maliyet matrisiyle O(n^2).
 * Notlardaki ornek: 6 dugumlu cizge (Horowitz-Sahni). Kaynak 0: 2 -> 10,
 * 3 -> 25, 1 -> 45, 4 -> 45, 5'e yol yok. Kaynak 2: 0 -> 20, 3 -> 15,
 * 1 -> 35, 4 -> 45.
 * Slaytlar: "Kod: Veri ve minimumBul", "EnKisaYolBul()", "Dijkstra Adim Adim",
 * "Yolu Bulmak Adim Adim". */
#include <stdio.h>
#include <limits.h>
#define MAX_DUGUM 6
#define SONSUZ 1000      /* baglanti yok */
#define TRUE  1          /* sunumda yok: Bolum 15'teki TRUE/FALSE */
#define FALSE 0
int maliyet[][MAX_DUGUM] = {
    {   0,   50,  10, 1000,   45, 1000},
    {1000,    0,  15, 1000,   10, 1000},
    {  20, 1000,   0,   15, 1000, 1000},
    {1000,   20, 1000,   0,   35, 1000},
    {1000, 1000, 1000,  30,    0, 1000},   /* eksik satir */
    {1000, 1000, 1000,   3, 1000,    0}};  /* 100 -> 1000 */
int minimumBul(int uzaklik[], int n, short gidildi[])
{
    int i, min = INT_MAX, pos = -1;
    for (i = 0; i < n; i++)
        if (uzaklik[i] < min && !gidildi[i]) {
            min = uzaklik[i];  pos = i;
        }
    return pos;
}

void EnKisaYolBul(int v, int maliyet[][MAX_DUGUM],
                  int uzaklik[], int onceki[],
                  int n, short gidildi[])
{
    int i, u, w;
    for (i = 0; i < n; i++) {                  /* A1 */
        gidildi[i] = FALSE;
        uzaklik[i] = maliyet[v][i];
        onceki[i] = v;             /* yol icin tutulur */
    }
    gidildi[v] = TRUE;  uzaklik[v] = 0;
    for (i = 2; i < n; i++) {        /* n-2 tur */
        u = minimumBul(uzaklik, n, gidildi);
        if (u < 0) break;            /* kalan yok */
        gidildi[u] = TRUE;
        for (w = 0; w < n; w++)
            if (!gidildi[w] &&
                uzaklik[u] + maliyet[u][w] < uzaklik[w]) {
                uzaklik[w] = uzaklik[u] + maliyet[u][w];
                onceki[w] = u;
            }
    }
}

void yol_yaz(int onceki[], int s, int h)
{
    if (h == s) {
        printf("%d", s);
        return;
    }
    yol_yaz(onceki, s, onceki[h]);   /* once oncul */
    printf(" -> %d", h);
}

/* sunumda yok: bir kaynaktan butun sonuclari yazar; erisilemeyen dugumde
 * onceki[] anlamsiz oldugu icin once uzaklik denetlenir */
static void sonuc_yaz(int s)
{
    int uzaklik[MAX_DUGUM], onceki[MAX_DUGUM], h;
    short gidildi[MAX_DUGUM];
    EnKisaYolBul(s, maliyet, uzaklik, onceki, MAX_DUGUM, gidildi);
    printf("kaynak %d:\n", s);
    for (h = 0; h < MAX_DUGUM; h++) {
        if (uzaklik[h] >= SONSUZ) {
            printf("  %d: yol yok\n", h);
            continue;
        }
        printf("  %d: %d  ", h, uzaklik[h]);
        yol_yaz(onceki, s, h);
        printf("\n");
    }
}

int main(void)
{
    sonuc_yaz(0);
    sonuc_yaz(2);
    return 0;
}

/* Beklenen cikti:
 * kaynak 0:
 *   0: 0  0
 *   1: 45  0 -> 2 -> 3 -> 1
 *   2: 10  0 -> 2
 *   3: 25  0 -> 2 -> 3
 *   4: 45  0 -> 4
 *   5: yol yok
 * kaynak 2:
 *   0: 20  2 -> 0
 *   1: 35  2 -> 3 -> 1
 *   2: 0  2
 *   3: 15  2 -> 3
 *   4: 45  2 -> 3 -> 1 -> 4
 *   5: yol yok
 */
