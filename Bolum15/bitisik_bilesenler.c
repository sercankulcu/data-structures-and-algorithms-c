/* Baglantili bilesenler: isaretsiz her dugumden yeni bir dfs baslatilir; her
 * bilesen ayri satira yazilir. Toplam is O(n + e) (carpim degil, toplam).
 * Slayttaki ornek: 10 dugum, kenarlar (0,1) (0,2) (1,3) (2,3) (4,5) (4,6)
 * (7,8) (8,9); cikti 0 1 3 2 / 4 5 6 / 7 8 9.
 * Slaytlar: "Baglantili Bilesenler", "Bilesenler Adim Adim". */
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

void bitisik_bilesenler(int n)
{
    int i;
    for (i = 0; i < n; i++)
        if (!ugranildi[i]) {   /* yeni */
            dfs(i);
            printf("\n");
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
    static const int k[8][2] = {
        {0, 1}, {0, 2}, {1, 3}, {2, 3},
        {4, 5}, {4, 6}, {7, 8}, {8, 9}
    };
    liste_kur(k, 8);
    bitisik_bilesenler(10);
    listeleri_birak(baslik, 10);
    return 0;
}

/* Not: her sayidan sonra bir bosluk vardir. */
/* Beklenen cikti:
 * 0 1 3 2
 * 4 5 6
 * 7 8 9
 */
