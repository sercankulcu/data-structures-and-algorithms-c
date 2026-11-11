/* Genislik oncelikli arama (BFS) ve bagli listeyle dinamik kuyruk
 * (kuyruk_ekle, kuyruk_al). Dugum kuyruga eklenirken isaretlenir.
 * Notlardaki ornek: DFS ile ayni 8 dugumlu cizge, listeler sirali.
 * bfs(0) = 0 1 2 3 4 5 6 7, bfs(7) = 7 3 4 5 6 1 2 0.
 * Slaytlar: "BFS: Algoritma", "BFS: Dinamik Kuyruk", "BFS Adim Adim"
 * (ve devami). */
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

typedef struct kuyruk *kuyruk_gost;
typedef struct kuyruk {
    int dugum;
    kuyruk_gost bag;
} kuyruk;
void kuyruk_ekle(kuyruk_gost *on,
                 kuyruk_gost *arka, int d)
{
    kuyruk_gost p = malloc(sizeof(kuyruk));
    if (p == NULL) exit(1);
    p->dugum = d;  p->bag = NULL;
    if (*on) (*arka)->bag = p;  else *on = p;
    *arka = p;
}

int kuyruk_al(kuyruk_gost *on,
              kuyruk_gost *arka)
{
    kuyruk_gost p = *on;   /* on != NULL */
    int d = p->dugum;
    *on = p->bag;
    if (*on == NULL) *arka = NULL;
    free(p);
    return d;
}

void bfs(int v)   /* once genisligine arama */
{
    oge_gost w;
    kuyruk_gost on = NULL, arka = NULL;
    printf("%d ", v);
    ugranildi[v] = TRUE;
    kuyruk_ekle(&on, &arka, v);
    while (on) {
        v = kuyruk_al(&on, &arka);
        for (w = baslik[v]; w; w = w->bag)
            if (!ugranildi[w->dugum]) {
                printf("%d ", w->dugum);
                kuyruk_ekle(&on, &arka, w->dugum);
                ugranildi[w->dugum] = TRUE;
            }
    }
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

    printf("bfs(0): ");
    bfs(0);
    printf("\n");

    for (i = 0; i < 8; i++) ugranildi[i] = FALSE;   /* isaretleri sil */
    printf("bfs(7): ");
    bfs(7);
    printf("\n");

    listeleri_birak(baslik, 8);
    return 0;
}

/* Not: her sayidan sonra bir bosluk vardir. */
/* Beklenen cikti:
 * bfs(0): 0 1 2 3 4 5 6 7
 * bfs(7): 7 3 4 5 6 1 2 0
 */
