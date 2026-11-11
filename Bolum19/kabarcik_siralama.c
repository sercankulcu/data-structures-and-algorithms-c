/* Kabarcik siralamasi (bubble): her turda sagdan sola komsular karsilastirilir,
 * en kucuk oge sola yukselir. Ornek, notlardaki izlemenin dizisi [7, 2, 9, 5, 1].
 * Slayt: "Kabarcik Siralamasi". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: makro "Ortak Altyapi: Makrolar" slaytindan */
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void bubble(int a[], int L, int R) {
    int i, j;
    for (i = L; i < R; i++)
        for (j = R; j > i; j--)
            if (a[j] < a[j-1]) SWAP(a[j], a[j-1]);
}

int main(void) {   /* sunumda yok */
    int a[] = {7, 2, 9, 5, 1};
    bubble(a, 0, 4);
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti (sonda bosluk var):
 * 1 2 5 7 9 
 */
