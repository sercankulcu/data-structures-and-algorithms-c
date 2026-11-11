/* sunumda yok: liste.h arayuzunun dinamik dizi ile gerceklemesi (ders
 * notundaki surum). Kapasite 4 ile baslar, dizi dolunca iki katina cikar.
 * struct liste yalniz bu dosyada tanimlidir (opak tur). */
#include <stdlib.h>
#include "liste.h"

// liste.c: struct liste yalnız burada tanımlıdır (opak tür)
struct liste {
    int *a;                             // heap'teki dizi
    int n, kap;                         // öğe sayısı, kapasite
};

Liste *liste_olustur(void) {
    Liste *L = malloc(sizeof *L);
    if (L == NULL) return NULL;
    L->n = 0;
    L->kap = 4;
    L->a = malloc(L->kap * sizeof *L->a);
    if (L->a == NULL) { free(L); return NULL; }
    return L;
}

void liste_yok_et(Liste *L) {
    if (L) { free(L->a); free(L); }
}

int liste_uzunluk(const Liste *L) { return L->n; }

bool liste_getir(const Liste *L, int i, int *x) {
    if (i < 0 || i >= L->n) return false;
    *x = L->a[i];
    return true;
}

bool liste_ekle(Liste *L, int i, int x) {
    int k;
    if (i < 0 || i > L->n) return false;
    if (L->n == L->kap) {               // dolu: iki katına çıkar
        int *yeni = realloc(L->a, 2 * L->kap * sizeof *L->a);
        if (yeni == NULL) return false; // eski dizi yerinde kalır
        L->a = yeni;
        L->kap *= 2;
    }
    for (k = L->n; k > i; k--)
        L->a[k] = L->a[k - 1];
    L->a[i] = x;
    L->n++;
    return true;
}

bool liste_sil(Liste *L, int i, int *x) {
    int k;
    if (i < 0 || i >= L->n) return false;
    *x = L->a[i];
    for (k = i; k < L->n - 1; k++)
        L->a[k] = L->a[k + 1];
    L->n--;
    return true;
}

int liste_ara(const Liste *L, int x) {
    for (int k = 0; k < L->n; k++)
        if (L->a[k] == x) return k;
    return -1;
}
