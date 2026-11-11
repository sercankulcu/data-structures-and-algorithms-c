/* Siralama yordamlarini sinamak icin ortak altyapi: kucuk ve SWAP makrolari ile
 * N = 15 rastgele sayiyi (rand() % 50) secimli siralamayla siralayan ana program.
 * rand() tohumsuz cagrildigi icin her calistirmada ayni diziyi uretir; sayilar
 * C kutuphanesine baglidir. Beklenen cikti glibc (Linux, CI) icindir.
 * Slaytlar: "Ortak Altyapi: Makrolar", "Secimli Siralama". */
#include <stdio.h>   /* sunumda yok: printf */
#include <stdlib.h>  /* sunumda yok: malloc, free, rand */

#define N 15
#define kucuk(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

/* sunumda ayri slaytta: main'den once tanimlandi */
void selection(int a[], int L, int R) {
    for (int i = L; i < R; i++) {
        int min = i;
        for (int j = i + 1; j <= R; j++)
            if (kucuk(a[j], a[min]))
                min = j;
        SWAP(a[i], a[min]);
    }
}

int main(void) {
    int *a = malloc(N * sizeof *a);
    if (a == NULL) return 1;
    for (int i = 0; i < N; i++)
        a[i] = rand() % 50;
    selection(a, 0, N - 1);   /* sıralama yordamına çağrı */
    for (int i = 0; i < N; i++) printf("%d ", a[i]);
    free(a);
    return 0;
}

/* Beklenen cikti (glibc; sonda bosluk var, satir sonu yok):
 * 9 12 13 15 21 27 27 33 35 36 36 40 42 43 49 
 */
