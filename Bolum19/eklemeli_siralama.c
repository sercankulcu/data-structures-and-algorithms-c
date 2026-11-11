/* Eklemeli siralama (insertion): a[i], sirali on ek a[L..i-1] icinde
 * sagdan sola kaydirilarak yerine konur. Notlardaki iki ornek: [7, 2, 9, 5, 1]
 * dizisinin tamami ve [9, 8, 7, 1, 6, 5, 0] dizisinde yalniz a[2..5] (j >= L
 * siniri sayesinde a[0], a[1] ve a[6]'ya dokunulmaz).
 * Slaytlar: "Eklemeli Siralama", "insertion() Adim Adim". */
#include <stdio.h>   /* sunumda yok */

void insertion(int a[], int L, int R) {
    for (int i = L + 1; i <= R; i++) {
        int v = a[i];      // yerleştirilecek
        int j = i - 1;     // a[L..i-1] sıralı
        while (j >= L && a[j] > v) {
            a[j + 1] = a[j]; // sağa kaydır
            j--;
        }
        a[j + 1] = v;
    }
}

/* sunumda yok: diziyi yazdirir */
static void yazdir(const char *ad, const int a[], int n) {
    printf("%s", ad);
    for (int i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void) {   /* sunumda yok */
    int a[] = {7, 2, 9, 5, 1};
    insertion(a, 0, 4);
    yazdir("insertion(a, 0, 4):", a, 5);

    int b[] = {9, 8, 7, 1, 6, 5, 0};
    insertion(b, 2, 5);
    yazdir("insertion(b, 2, 5):", b, 7);
    return 0;
}

/* Beklenen cikti:
 * insertion(a, 0, 4): 1 2 5 7 9
 * insertion(b, 2, 5): 9 8 1 5 6 7 0
 */
