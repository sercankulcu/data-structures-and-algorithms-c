/* Yonsuz cizgede dongu tespiti: DFS ebeveyn (ata) disinda isaretli bir
 * komsuya rastlarsa geri kenar, yani dongu vardir.
 * Notlardaki ornekler: kenarlari 0-1, 1-2, 2-3, 3-1 olan cizgede
 * dongu_var(0, -1) TRUE (geri kenar (3,1)); agac olan G2'de FALSE.
 * Slayt: "Dongu Tespiti". */
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

bool dongu_var(int v, int ata)
{
    oge_gost w;
    ugranildi[v] = TRUE;
    for (w = baslik[v]; w; w = w->bag)
        if (!ugranildi[w->dugum]) {
            if (dongu_var(w->dugum, v)) return TRUE;
        } else if (w->dugum != ata)
            return TRUE;          /* geri kenar */
    return FALSE;
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
    static const int dongulu[4][2] = { {0, 1}, {1, 2}, {1, 3}, {2, 3} };
    static const int g2[6][2] = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}
    };
    int i;

    liste_kur(dongulu, 4);
    printf("0-1, 1-2, 2-3, 3-1: dongu_var(0, -1) = %d\n", dongu_var(0, -1));
    listeleri_birak(baslik, 4);

    for (i = 0; i < MAX_DUGUM; i++) ugranildi[i] = FALSE;   /* isaretleri sil */
    liste_kur(g2, 6);
    printf("G2 (agac): dongu_var(0, -1) = %d\n", dongu_var(0, -1));
    listeleri_birak(baslik, 7);
    return 0;
}

/* Beklenen cikti:
 * 0-1, 1-2, 2-3, 3-1: dongu_var(0, -1) = 1
 * G2 (agac): dongu_var(0, -1) = 0
 */
