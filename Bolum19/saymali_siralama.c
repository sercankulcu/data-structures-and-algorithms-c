/* Saymali siralama (counting_sort): degerler 0..k araligindaki tamsayilardir.
 * L1 sayaclari sifirlar, L2 sayar, L3 biriktirir (c[x] = x'ten kucuk ya da esit
 * oge sayisi), L4 girdiyi sagdan sola gezip b'ye kararli bicimde yerlestirir.
 * Ornek, notlardaki a = [3, 0, 6, 9, 4, 3, 10, 5], r = 7, k = 10.
 * Slaytlar: "Saymali Siralama", "counting_sort(): Sayma",
 * "counting_sort(): Yerlestirme". */
#include <stdio.h>   /* sunumda yok */
#include <stdlib.h>  /* sunumda yok: malloc, free */

int counting_sort(const int a[], int b[],
                  int r, int k) {
    int *c = malloc((k + 1) * sizeof *c);
    if (c == NULL) return -1;
    for (int i = 0; i <= k; i++) c[i] = 0;  // L1
    for (int j = 0; j <= r; j++) c[a[j]]++; // L2
    for (int i = 1; i <= k; i++)            // L3
        c[i] += c[i - 1];
    for (int j = r; j >= 0; j--) {          // L4
        b[c[a[j]] - 1] = a[j];
        c[a[j]]--;
    }
    free(c);
    return 0;
}

int main(void) {   /* sunumda yok */
    const int a[] = {3, 0, 6, 9, 4, 3, 10, 5};
    int b[8];
    if (counting_sort(a, b, 7, 10) != 0) return 1;
    for (int i = 0; i < 8; i++) printf("%d ", b[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti (sonda bosluk var):
 * 0 3 3 4 5 6 9 10 
 */
