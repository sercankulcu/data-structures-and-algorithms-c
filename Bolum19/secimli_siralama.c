/* Secimli siralama (selection): her turda a[i..R]'nin en kucugu bulunur ve
 * a[i] ile takaslanir. Ornek, notlardaki izlemenin dizisi [29, 10, 14, 37, 13].
 * Slaytlar: "Secimli Siralama", "selection() Adim Adim". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: makrolar "Ortak Altyapi: Makrolar" slaytindan */
#define kucuk(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void selection(int a[], int L, int R) {
    for (int i = L; i < R; i++) {
        int min = i;
        for (int j = i + 1; j <= R; j++)
            if (kucuk(a[j], a[min]))
                min = j;
        SWAP(a[i], a[min]);
    }
}

/* sunumda yok: diziyi yazdirir */
static void yazdir(const char *ad, const int a[], int n) {
    printf("%s", ad);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* sunumda yok */
    int a[] = {29, 10, 14, 37, 13};
    yazdir("once: ", a, 5);
    selection(a, 0, 4);
    yazdir("sonra:", a, 5);
    return 0;
}

/* Beklenen cikti:
 * once:  29 10 14 37 13
 * sonra: 10 13 14 29 37
 */
