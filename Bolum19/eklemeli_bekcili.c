/* Bekcili eklemeli siralama (insertion1): once sagdan sola bir gecisle en
 * kucuk oge a[L]'ye tasinir; o bekci oldugu icin ic dongu j >= L sinamasina
 * gerek duymaz. Ornek, notlardaki izlemenin dizisi [4, 3, 1, 2].
 * Slaytlar: "Eklemeli Siralama", "insertion1() Adim Adim". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: makrolar "Ortak Altyapi: Makrolar" slaytindan */
#define kucuk(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void insertion1(int a[], int L, int R) {
    for (int i = R; i > L; i--) // bekçi
        if (a[i] < a[i-1]) SWAP(a[i], a[i-1]);
    for (int i = L + 2; i <= R; i++) {
        int v = a[i], j = i;
        while (kucuk(v, a[j - 1])) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = v;
    }
}

int main(void) {   /* sunumda yok */
    int a[] = {4, 3, 1, 2};
    insertion1(a, 0, 3);
    for (int i = 0; i < 4; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti (sonda bosluk var):
 * 1 2 3 4 
 */
