/* C kitapligindaki qsort ve karsilastirma fonksiyonu artan. Donus degeri
 * (x > y) - (x < y) hicbir degerde tasmaz (x - y tasabilir).
 * Slayt: "qsort Kullanimi". */
#include <stdio.h>   /* sunumda yok */
#include <stdlib.h>  /* sunumda yok: qsort */

int artan(const void *p, const void *q) {
    int x = *(const int *)p;
    int y = *(const int *)q;
    return (x > y) - (x < y);  // -1, 0, +1
}
int main(void) {
    int a[] = {37, 15, 24, 33, 49};
    size_t n = sizeof a / sizeof a[0];
    qsort(a, n, sizeof a[0], artan);
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}

/* Beklenen cikti (sonda bosluk var, satir sonu yok):
 * 15 24 33 37 49
 */
