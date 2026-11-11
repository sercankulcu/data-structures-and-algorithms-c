/* Shell siralamasi (shell_sort): aralik h = n/2, n/4, ..., 1 icin aralikli
 * eklemeli siralama. Ornek, notlardaki izlemenin dizisi
 * [35, 33, 42, 10, 14, 19, 27, 44]; h = 4 ve h = 2 turlarindan sonra dizi
 * [14, 19, 27, 10, 35, 33, 42, 44] ve [14, 10, 27, 19, 35, 33, 42, 44] olur.
 * Slayt: "shell_sort() Adim Adim". */
#include <stdio.h>   /* sunumda yok */

void shell_sort(int a[], int n) {
    for (int h = n / 2; h > 0; h /= 2) // aralık
        for (int i = h; i < n; i++) {
            int v = a[i], j = i;
            while (j >= h && a[j - h] > v) {
                a[j] = a[j - h];    // h geri kaydır
                j -= h;
            }
            a[j] = v;
        }
}

int main(void) {   /* sunumda yok */
    int a[] = {35, 33, 42, 10, 14, 19, 27, 44};
    shell_sort(a, 8);
    for (int i = 0; i < 8; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti (sonda bosluk var):
 * 10 14 19 27 33 35 42 44 
 */
