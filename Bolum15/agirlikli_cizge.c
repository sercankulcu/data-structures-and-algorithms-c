/* Agirlikli cizgenin iki gosterimi: maliyet matrisi (kenar yoksa SONSUZ,
 * kosegen 0) ve her ogede agirlik alani olan komsuluk listesi.
 * Notlardaki ornek: A-B 4, A-C 2, B-C 1, B-D 5, C-D 8 (A=0, B=1, C=2, D=3).
 * Slayt: "Agirlikli Cizge Gosterimi". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_DUGUM 50   /* sunumda yok: "Komsuluk Listesi" slaytindaki sabit */

#define SONSUZ 1000000   /* INT_MAX degil: toplamda tasar */
int maliyet[MAX_DUGUM][MAX_DUGUM];

typedef struct aoge *aoge_gost;
typedef struct aoge {
    int dugum;
    int agirlik;        /* kenarin maliyeti */
    aoge_gost bag;
} aoge;
aoge_gost abaslik[MAX_DUGUM];

/* sunumda yok: abaslik[u] listesinin basina (v, w) ekler */
static void aekle(int u, int v, int w)
{
    aoge_gost p = malloc(sizeof(aoge));
    if (p == NULL) exit(1);
    p->dugum = v;
    p->agirlik = w;
    p->bag = abaslik[u];
    abaslik[u] = p;
}

/* sunumda yok: listeleri birakir */
static void abirak(int n)
{
    int i;
    aoge_gost p;
    for (i = 0; i < n; i++)
        while (abaslik[i]) {
            p = abaslik[i];
            abaslik[i] = p->bag;
            free(p);
        }
}

int main(void)
{
    const char *ad = "ABCD";
    int n = 4, i, j;
    aoge_gost p;

    /* sunumda yok: matrisi doldur */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            maliyet[i][j] = (i == j) ? 0 : SONSUZ;
    maliyet[0][1] = maliyet[1][0] = 4;
    maliyet[0][2] = maliyet[2][0] = 2;
    maliyet[1][2] = maliyet[2][1] = 1;
    maliyet[1][3] = maliyet[3][1] = 5;
    maliyet[2][3] = maliyet[3][2] = 8;

    /* listeyi matristen kur; j azalarak eklenince liste artan sirada olur */
    for (i = 0; i < n; i++)
        for (j = n - 1; j >= 0; j--)
            if (i != j && maliyet[i][j] != SONSUZ)
                aekle(i, j, maliyet[i][j]);

    printf("maliyet matrisi:\n");
    for (i = 0; i < n; i++) {
        printf("%c:", ad[i]);
        for (j = 0; j < n; j++)
            if (maliyet[i][j] == SONSUZ) printf(" oo");
            else printf(" %d", maliyet[i][j]);
        printf("\n");
    }
    printf("komsuluk listesi (komsu/agirlik):\n");
    for (i = 0; i < n; i++) {
        printf("%c:", ad[i]);
        for (p = abaslik[i]; p; p = p->bag)
            printf(" %c/%d", ad[p->dugum], p->agirlik);
        printf("\n");
    }
    abirak(n);
    return 0;
}

/* Beklenen cikti:
 * maliyet matrisi:
 * A: 0 4 2 oo
 * B: 4 0 1 5
 * C: 2 1 0 8
 * D: oo 5 8 0
 * komsuluk listesi (komsu/agirlik):
 * A: B/4 C/2
 * B: A/4 C/1 D/5
 * C: A/2 B/1 D/8
 * D: B/5 C/8
 */
