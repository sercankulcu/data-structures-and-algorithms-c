/* Derinlik oncelikli arama (DFS): ozyinelemeli, komsuluk listesiyle O(n + e).
 * Notlardaki ornek: 8 dugumlu, 10 kenarli cizge, listeler sirali:
 * 0:{1,2} 1:{0,3,4} 2:{0,5,6} 3:{1,7} 4:{1,7} 5:{2,7} 6:{2,7} 7:{3,4,5,6}.
 * dfs(0) = 0 1 3 7 4 5 2 6, dfs(7) = 7 3 1 0 2 5 6 4.
 * Slaytlar: "DFS: Algoritma ve Kod", "DFS Adim Adim" (ve devami). */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */
#define TRUE  true
#define FALSE false

#define MAX_DUGUM 50   /* en fazla dugum sayisi */
typedef struct oge *oge_gost;
typedef struct oge {
    int dugum;         /* komsu dugumun numarasi */
    oge_gost bag;      /* listedeki sonraki komsu */
} oge;                 /* ';' ve typedef adi unutulmamali */
oge_gost baslik[MAX_DUGUM];   /* her dugume bir liste */

bool ugranildi[MAX_DUGUM];   /* ';' unutulmamali */

void dfs(int v)   /* once derinligine arama */
{
    oge_gost w;
    ugranildi[v] = TRUE;    /* ugradim */
    printf("%d ", v);
    for (w = baslik[v]; w; w = w->bag)
        if (!ugranildi[w->dugum])
            dfs(w->dugum);
}

/* sunumda yok: "Liste Kurma" slaytindaki kenar_ekle */
void kenar_ekle(int u, int v)   /* u -> v */
{
    oge_gost p = malloc(sizeof(oge));
    if (p == NULL) exit(1);       /* bellek yok */
    p->dugum = v;
    p->bag = baslik[u];   /* basa ekle: O(1) */
    baslik[u] = p;
}

/* sunumda yok: yonsuz kenarlari ters sirayla basa ekler; boylece her liste
 * artan sirada olur */
static void liste_kur(const int k[][2], int e)
{
    int i;
    for (i = e - 1; i >= 0; i--) {
        kenar_ekle(k[i][0], k[i][1]);
        kenar_ekle(k[i][1], k[i][0]);
    }
}

/* sunumda yok: ders notundaki listeleri_birak */
void listeleri_birak(oge_gost bas[], int n)
{
    int i;
    oge_gost p;
    for (i = 0; i < n; i++) {
        while (bas[i]) {
            p = bas[i];
            bas[i] = p->bag;   /* once bag saklanir */
            free(p);
        }
    }
}

int main(void)
{
    static const int k[10][2] = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5},
        {2, 6}, {3, 7}, {4, 7}, {5, 7}, {6, 7}
    };
    int i;
    liste_kur(k, 10);

    printf("dfs(0): ");
    dfs(0);
    printf("\n");

    for (i = 0; i < 8; i++) ugranildi[i] = FALSE;   /* isaretleri sil */
    printf("dfs(7): ");
    dfs(7);
    printf("\n");

    listeleri_birak(baslik, 8);
    return 0;
}

/* Not: her sayidan sonra bir bosluk vardir. */
/* Beklenen cikti:
 * dfs(0): 0 1 3 7 4 5 2 6
 * dfs(7): 7 3 1 0 2 5 6 4
 */
