/* Komsuluk matrisiyle yonlu cizgede derece: satir toplami cikis, sutun
 * toplami giris derecesi. Notlardaki ornek: G3 (<0,1>, <1,0>, <1,2>);
 * derece(a, 3, 1) = 2 + 1 = 3.
 * Slayt: "Matriste Derece Adim Adim". */
#include <stdio.h>

#define MAX_DUGUM 50   /* sunumda yok: "Komsuluk Listesi" slaytindaki sabit */

int derece(int a[][MAX_DUGUM], int n, int v)
{
    int j, cikis = 0, giris = 0;
    for (j = 0; j < n; j++)
        cikis += a[v][j];      /* satir  */
    for (j = 0; j < n; j++)
        giris += a[j][v];      /* sutun */
    return cikis + giris;
}

/* sunumda yok: G3'un komsuluk matrisi (kalan hucreler 0) */
static int a[MAX_DUGUM][MAX_DUGUM] = {
    {0, 1, 0},
    {1, 0, 1},
    {0, 0, 0}
};

int main(void)
{
    int v;
    for (v = 0; v < 3; v++)
        printf("derece(a, 3, %d) = %d\n", v, derece(a, 3, v));
    return 0;
}

/* Beklenen cikti:
 * derece(a, 3, 0) = 2
 * derece(a, 3, 1) = 3
 * derece(a, 3, 2) = 1
 */
