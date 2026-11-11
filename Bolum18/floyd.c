/* Floyd-Warshall: ara dugum k disarida, A[i][j] = min(A[i][j],
 * A[i][k] + A[k][j]); tum ciftler arasi en kisa yollar, Theta(n^3).
 * Notlardaki ornekler: Horowitz'in uc dugumlu matrisi (sonuc 0 4 6 / 5 0 2 /
 * 3 7 0) ve bolumun 6 dugumlu ana cizgesi (0. satir Dijkstra ile ayni).
 * Slayt: "Floyd-Warshall Adim Adim" (yordam basligi ders notundan). */
#include <stdio.h>

#define MAX_DUGUM 6      /* sunumda yok: bolumdeki sabitler */
#define SONSUZ 1000

/* sunumda yok: ders notundaki yordam basligi */
void Floyd(int maliyet[][MAX_DUGUM], int A[][MAX_DUGUM], int n)
{
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            A[i][j] = maliyet[i][j];
    for (k = 0; k < n; k++)              /* ara dugum k */
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (A[i][k] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
}

/* sunumda yok: matrisi yazar (SONSUZ yerine oo) */
static void yaz(int A[][MAX_DUGUM], int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            if (A[i][j] >= SONSUZ) printf("   oo");
            else printf(" %4d", A[i][j]);
        printf("\n");
    }
}

int main(void)
{
    int uc[MAX_DUGUM][MAX_DUGUM] = {
        {0, 4, 11},
        {6, 0, 2},
        {3, SONSUZ, 0}
    };
    int alti[MAX_DUGUM][MAX_DUGUM] = {
        {   0,   50,  10, 1000,   45, 1000},
        {1000,    0,  15, 1000,   10, 1000},
        {  20, 1000,   0,   15, 1000, 1000},
        {1000,   20, 1000,   0,   35, 1000},
        {1000, 1000, 1000,  30,    0, 1000},
        {1000, 1000, 1000,   3, 1000,    0}};
    int A[MAX_DUGUM][MAX_DUGUM];

    Floyd(uc, A, 3);
    printf("uc dugum:\n");
    yaz(A, 3);
    Floyd(alti, A, 6);
    printf("alti dugum:\n");
    yaz(A, 6);
    return 0;
}

/* Beklenen cikti:
 * uc dugum:
 *     0    4    6
 *     5    0    2
 *     3    7    0
 * alti dugum:
 *     0   45   10   25   45   oo
 *    35    0   15   30   10   oo
 *    20   35    0   15   45   oo
 *    55   20   35    0   30   oo
 *    85   50   65   30    0   oo
 *    58   23   38    3   33    0
 */
