/* Listenin dizi ile (sirali yerlesim) gerceklenmesi: dizi_ekle oge icin
 * yer acarken saga, dizi_sil bosluk kapatirken sola kaydirir. Ornek
 * liste [4, 7, 2]; 1. konuma 9 eklenir, sonra bastan silinir; gecersiz
 * konumlar false ile reddedilir.
 * Slaytlar: "Dizi ile Gercekleme", "Dizi ile Ekleme Adim Adim". */
#include <stdio.h>
#include <stdbool.h>  /* sunumda yok: bool */

#define KAPASITE 100
typedef struct {
    int a[KAPASITE];
    int n;                  // öğe sayısı
} DiziListe;

bool dizi_sil(DiziListe *L, int i, int *x) {
    int k;
    if (i < 0 || i >= L->n) return false;
    *x = L->a[i];
    for (k = i; k < L->n - 1; k++)
        L->a[k] = L->a[k + 1];      // sola kaydır
    L->n--;
    return true;
}

bool dizi_ekle(DiziListe *L, int i, int x) {
    int k;
    if (L->n == KAPASITE || i < 0 || i > L->n)
        return false;          // dolu/geçersiz
    for (k = L->n; k > i; k--)
        L->a[k] = L->a[k - 1];     // sağa kaydır
    L->a[i] = x;
    L->n++;
    return true;
}

/* sunumda yok: listeyi yazar */
static void yaz(const DiziListe *L)
{
    int k;
    printf("[");
    for (k = 0; k < L->n; k++)
        printf(k ? ", %d" : "%d", L->a[k]);
    printf("] n = %d\n", L->n);
}

int main(void)
{
    DiziListe L = { {4, 7, 2}, 3 };
    int x = 0, r;

    printf("baslangic: ");
    yaz(&L);

    r = dizi_ekle(&L, 1, 9);
    printf("dizi_ekle(&L, 1, 9) = %d: ", r);
    yaz(&L);

    r = dizi_sil(&L, 0, &x);
    printf("dizi_sil(&L, 0, &x) = %d, x = %d: ", r, x);
    yaz(&L);

    r = dizi_ekle(&L, 5, 1);
    printf("dizi_ekle(&L, 5, 1) = %d\n", r);
    r = dizi_sil(&L, 3, &x);
    printf("dizi_sil(&L, 3, &x) = %d\n", r);
    return 0;
}

/* Beklenen cikti:
 * baslangic: [4, 7, 2] n = 3
 * dizi_ekle(&L, 1, 9) = 1: [4, 9, 7, 2] n = 4
 * dizi_sil(&L, 0, &x) = 1, x = 4: [9, 7, 2] n = 3
 * dizi_ekle(&L, 5, 1) = 0
 * dizi_sil(&L, 3, &x) = 0
 */
