/* Erken duran kabarcik siralamasi (bubble2): takassiz biten turdan sonra dizi
 * siralidir ve yordam doner. Ornek, notlardaki [2, 1, 3, 5, 4] dizisi; ikinci
 * tur takassiz biter ve yordam doner.
 * Slayt: "bubble2() Adim Adim". */
#include <stdio.h>   /* sunumda yok */

/* sunumda yok: makrolar "Ortak Altyapi: Makrolar" slaytindan */
#define kucuk(A, B) ((A) < (B))
#define SWAP(A, B) do { int t_ = (A); (A) = (B); (B) = t_; } while (0)

void bubble2(int a[], int L, int R) {
    for (int i = L; i < R; i++) {
        int takas = 0;      // bu turda takas oldu mu?
        for (int j = R; j > i; j--)
            if (kucuk(a[j], a[j - 1])) {
                SWAP(a[j], a[j - 1]);
                takas = 1;
            }
        if (!takas) return; // sıralı: erken çık
    }
}

int main(void) {   /* sunumda yok */
    int a[] = {2, 1, 3, 5, 4};
    bubble2(a, 0, 4);
    for (int i = 0; i < 5; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti (sonda bosluk var):
 * 1 2 3 4 5 
 */
