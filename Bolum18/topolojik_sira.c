/* Topolojik siralama (AoV agi): sayacli basliklar oncul sayisini tutar;
 * sayaci 0 olan dugumler sayac alaninin icine gomulu bir yiginda bekler.
 * Yigin bosalirken yazilmamis dugum kalirsa cizgede dongu vardir.
 * Notlardaki ornek: <0,1>, <0,2>, <0,3>, <1,4>, <2,4>, <2,5>, <3,5>, <3,4>
 * (listeler bu sirayla, sona eklenerek kurulur); cikti 0 3 2 5 1 4.
 * Ikinci ornek (sunumda yok): 0->1, 1->2, 2->1 dongusu; cikti "0 dongu".
 * Slaytlar: "Veri Yapisi: Sayacli Basliklar", "TopolojikSira()",
 * "Topolojik Sira Adim Adim" (ve devami). */
#include <stdio.h>
#include <stdlib.h>

#define MAX_DUGUM 6   /* sunumda yok: bolumdeki sabit */

typedef struct oge *oge_gost;
typedef struct oge {
    int dugum;
    oge_gost bag;
} oge;
typedef struct {
    int sayac;      /* <i,j> icin: basi j olan kenar sayisi */
    oge_gost bag;
} basoge;
basoge baslik[MAX_DUGUM];

void TopolojikSira(basoge baslik[], int n)
{
    int i, j, k, ust = -1;
    oge_gost p;
    for (i = 0; i < n; i++)      /* sayac 0: yigina */
        if (!baslik[i].sayac) {
            baslik[i].sayac = ust;  ust = i; }
    for (i = 0; i < n; i++) {
        if (ust == -1) { printf("dongu"); break; }
        j = ust;  ust = baslik[ust].sayac;
        printf("%d ", j);
        for (p = baslik[j].bag; p; p = p->bag) {
            k = p->dugum;
            if (--baslik[k].sayac == 0) {
                baslik[k].sayac = ust;  ust = k; }
        }
    }
}

/* sunumda yok: ders notundaki kenar_ekle (sona ekler, sayaci artirir) */
int kenar_ekle(basoge baslik[], int i, int j)
{
    oge_gost *son = &baslik[i].bag;   /* bag alaninin adresi */
    oge_gost yeni = malloc(sizeof(oge));
    if (yeni == NULL)
        return 0;                     /* bellek yetmedi */
    yeni->dugum = j;
    yeni->bag = NULL;
    while (*son != NULL)              /* listenin sonunu bul */
        son = &(*son)->bag;
    *son = yeni;
    baslik[j].sayac++;                /* j'nin bir onculu daha var */
    return 1;
}

/* sunumda yok: ders notundaki listeleri_birak */
void listeleri_birak(basoge baslik[], int n)
{
    int i;
    oge_gost p, sonraki;
    for (i = 0; i < n; i++) {
        for (p = baslik[i].bag; p; p = sonraki) {
            sonraki = p->bag;         /* free'den once sakla */
            free(p);
        }
        baslik[i].bag = NULL;
        baslik[i].sayac = 0;
    }
}

int main(void)
{
    static const int ag[8][2] = {
        {0, 1}, {0, 2}, {0, 3}, {1, 4}, {2, 4}, {2, 5}, {3, 5}, {3, 4}
    };
    static const int dongulu[3][2] = { {0, 1}, {1, 2}, {2, 1} };
    int i;

    for (i = 0; i < 8; i++)
        if (!kenar_ekle(baslik, ag[i][0], ag[i][1])) exit(1);
    TopolojikSira(baslik, 6);
    printf("\n");
    listeleri_birak(baslik, 6);

    for (i = 0; i < 3; i++)
        if (!kenar_ekle(baslik, dongulu[i][0], dongulu[i][1])) exit(1);
    TopolojikSira(baslik, 3);
    printf("\n");
    listeleri_birak(baslik, 3);
    return 0;
}

/* Not: her sayidan sonra bir bosluk vardir. */
/* Beklenen cikti:
 * 0 3 2 5 1 4
 * 0 dongu
 */
