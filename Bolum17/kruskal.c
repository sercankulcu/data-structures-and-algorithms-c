/* Kruskal: kenarlar qsort ile maliyete gore siralanir; dongu kurmayan kenar
 * (uclarinin kokleri farkli) agaca alinir. Kumeler agirlikli birlestir ve
 * kume_bul ile tutulur.
 * Notlardaki ornek: yedi koy cizgesi, 9 kenar; minimum kapsayan agacin
 * maliyeti 99, son ata dizisi 1 -7 1 2 1 0 1.
 * Slaytlar: "Union-Find ve Siralama", "Kruskal Kodu Adim Adim",
 * "Kruskal Kodu (devam)". */
#include <stdio.h>
#include <stdlib.h>

typedef struct { int u, v, w; } kenar;

int kume_bul(int ata[], int i)   /* kok: ata < 0 */
{
    while (ata[i] >= 0) i = ata[i];
    return i;
}
void birlestir(int ata[], int a, int b)   /* a, b kok */
{
    if (ata[a] <= ata[b]) {   /* a daha buyuk kume */
        ata[a] += ata[b];  ata[b] = a;
    } else {
        ata[b] += ata[a];  ata[a] = b;
    }
}
int kars(const void *x, const void *y)
{
    return ((const kenar *)x)->w - ((const kenar *)y)->w;
}

int main(void)
{
    /* sunumda yok: ornek cizge ve degiskenler */
    kenar k[] = {
        {0, 1, 28}, {0, 5, 10}, {1, 2, 16}, {1, 6, 14}, {2, 3, 12},
        {3, 4, 22}, {3, 6, 18}, {4, 5, 25}, {4, 6, 24}
    };
    int n = 7, e = 9, i, t, toplam = 0;
    int ata[7];
    kenar T[6];

    for (i = 0; i < n; i++) ata[i] = -1;
    qsort(k, e, sizeof(kenar), kars);
    for (i = 0, t = 0; i < e && t < n - 1; i++) {
        int a = kume_bul(ata, k[i].u);
        int b = kume_bul(ata, k[i].v);
        if (a != b) {                 /* dongu yok */
            T[t++] = k[i];
            birlestir(ata, a, b);
        }                             /* yoksa birak */
    }
    if (t < n - 1) printf("agac yok\n");

    /* sunumda yok: sonucu yaz */
    for (i = 0; i < t; i++) {
        printf("(%d,%d) %d\n", T[i].u, T[i].v, T[i].w);
        toplam += T[i].w;
    }
    printf("maliyet = %d\n", toplam);
    printf("ata =");
    for (i = 0; i < n; i++) printf(" %d", ata[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti:
 * (0,5) 10
 * (2,3) 12
 * (1,6) 14
 * (1,2) 16
 * (3,4) 22
 * (4,5) 25
 * maliyet = 99
 * ata = 1 -7 1 2 1 0 1
 */
