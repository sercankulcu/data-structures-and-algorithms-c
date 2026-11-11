/* Prim, dizilerle O(n^2): enaz[v] v'yi agaca baglayan en ucuz kenarin
 * maliyeti, yakin[v] o kenarin agactaki ucudur. Cizge maliyet matrisiyle
 * tutulur (kenar yoksa SONSUZ).
 * Notlardaki ornek: yedi koy cizgesi, 0'dan; dugumler 5, 4, 3, 2, 1, 6
 * sirasiyla agaca girer, toplam 99.
 * Slayt: "Prim Kodu Adim Adim". */
#include <stdio.h>

#define SONSUZ 1000000   /* sunumda yok: ders notundaki sabit */
#define N 7              /* sunumda yok: dugum sayisi */

/* sunumda yok: ders notundaki en_yakin (dogrusal arama) */
int en_yakin(const int enaz[], const int secildi[], int n)
{
    int v, u = -1;
    for (v = 0; v < n; v++)
        if (!secildi[v] && enaz[v] < SONSUZ &&
            (u < 0 || enaz[v] < enaz[u]))
            u = v;
    return u;            /* -1: TV'ye bagli dugum kalmadi */
}

int main(void)
{
    /* sunumda yok: ornek cizge ve degiskenler */
    static const int kenarlar[9][3] = {
        {0, 1, 28}, {0, 5, 10}, {1, 2, 16}, {1, 6, 14}, {2, 3, 12},
        {3, 4, 22}, {3, 6, 18}, {4, 5, 25}, {4, 6, 24}
    };
    int w[N][N], enaz[N], yakin[N], secildi[N] = {0};
    int n = N, k, u, v, toplam = 0;
    for (u = 0; u < n; u++)
        for (v = 0; v < n; v++)
            w[u][v] = (u == v) ? 0 : SONSUZ;
    for (k = 0; k < 9; k++) {
        w[kenarlar[k][0]][kenarlar[k][1]] = kenarlar[k][2];
        w[kenarlar[k][1]][kenarlar[k][0]] = kenarlar[k][2];
    }

    secildi[0] = 1;                    /* TV = {0} */
    for (v = 0; v < n; v++)
        enaz[v] = w[0][v], yakin[v] = 0;
    for (k = 1; k < n; k++) {
        u = en_yakin(enaz, secildi, n);  /* O(n) */
        if (u < 0) break;                /* agac yok */
        secildi[u] = 1;  toplam += enaz[u];
        printf("k=%d: (%d,%d) %d, toplam = %d\n",   /* sunumda yok */
               k, yakin[u], u, enaz[u], toplam);
        for (v = 0; v < n; v++)
            if (!secildi[v] && w[u][v] < enaz[v])
                enaz[v] = w[u][v], yakin[v] = u;
    }

    /* sunumda yok: son diziler */
    printf("enaz  =");
    for (v = 0; v < n; v++) printf(" %d", enaz[v]);
    printf("\nyakin =");
    for (v = 0; v < n; v++) printf(" %d", yakin[v]);
    printf("\n");
    return 0;
}

/* Beklenen cikti:
 * k=1: (0,5) 10, toplam = 10
 * k=2: (5,4) 25, toplam = 35
 * k=3: (4,3) 22, toplam = 57
 * k=4: (3,2) 12, toplam = 69
 * k=5: (2,1) 16, toplam = 85
 * k=6: (1,6) 14, toplam = 99
 * enaz  = 0 16 12 22 25 10 14
 * yakin = 0 2 3 4 5 0 1
 */
