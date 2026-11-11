/* Prim, komsuluk listesi ve ikili min-heap ile O(e log n): enaz kuculunce eski
 * kayit silinmez, yeni anahtarla bir kayit daha eklenir; agactaki dugumun
 * sonradan cikan kaydi bayattir ve atlanir.
 * Notlardaki ornek: yedi koy cizgesi; 10 kayit eklenir, 10 alinir, 3'u bayat;
 * agacin maliyeti 99.
 * Slayt: "Prim: Heap ile (ek)". */
#include <stdio.h>
#include <stdlib.h>

#define SONSUZ 1000000   /* sunumda yok: ders notundaki sabit */
#define MAX_DUGUM 50     /* sunumda yok: Bolum 15'teki sabit */

/* sunumda yok: agirlikli komsuluk listesi (Bolum 15, "Agirlikli Cizge
 * Gosterimi"), slayttaki baslik adiyla */
typedef struct aoge *aoge_gost;
typedef struct aoge {
    int dugum;
    int agirlik;        /* kenarin maliyeti */
    aoge_gost bag;
} aoge;
aoge_gost baslik[MAX_DUGUM];

/* sunumda yok: ders notundaki ikili min-heap */
typedef struct { int dugum, anahtar; } kayit;
typedef struct {
    kayit *a;          /* a[1..boyut]: kok a[1] */
    int boyut, kapasite;
} heap;
int heap_bos(const heap *H) { return H->boyut == 0; }
void heap_ekle(heap *H, int dugum, int anahtar)
{
    int i = ++H->boyut;                     /* kapasite >= 2e + 1 */
    while (i > 1 && H->a[i / 2].anahtar > anahtar) {
        H->a[i] = H->a[i / 2];              /* ebeveyni asagi indir */
        i /= 2;
    }
    H->a[i].dugum = dugum;  H->a[i].anahtar = anahtar;
}
int heap_min_al(heap *H)
{
    int kok = H->a[1].dugum;
    kayit son = H->a[H->boyut--];
    int i = 1, c = 2;
    while (c <= H->boyut) {
        if (c < H->boyut && H->a[c + 1].anahtar < H->a[c].anahtar) c++;
        if (son.anahtar <= H->a[c].anahtar) break;
        H->a[i] = H->a[c];                  /* kucuk cocugu yukari al */
        i = c;  c *= 2;
    }
    H->a[i] = son;
    return kok;
}

/* sunumda yok: baslik[u] listesinin basina (v, w) ekler */
static void aekle(int u, int v, int w)
{
    aoge_gost p = malloc(sizeof(aoge));
    if (p == NULL) exit(1);
    p->dugum = v;  p->agirlik = w;
    p->bag = baslik[u];
    baslik[u] = p;
}

int main(void)
{
    /* sunumda yok: ornek cizge, degiskenler ve heap */
    static const int kenarlar[9][3] = {
        {0, 1, 28}, {0, 5, 10}, {1, 2, 16}, {1, 6, 14}, {2, 3, 12},
        {3, 4, 22}, {3, 6, 18}, {4, 5, 25}, {4, 6, 24}
    };
    int n = 7, e = 9, u, v, toplam = 0;
    int enaz[MAX_DUGUM], yakin[MAX_DUGUM], secildi[MAX_DUGUM];
    aoge_gost p;
    heap yigin, *H = &yigin;

    for (v = 0; v < e; v++) {
        aekle(kenarlar[v][0], kenarlar[v][1], kenarlar[v][2]);
        aekle(kenarlar[v][1], kenarlar[v][0], kenarlar[v][2]);
    }
    for (v = 0; v < n; v++) {
        enaz[v] = SONSUZ;  yakin[v] = -1;  secildi[v] = 0;
    }
    enaz[0] = 0;
    yigin.kapasite = 2 * e + 2;
    yigin.boyut = 0;
    yigin.a = malloc(yigin.kapasite * sizeof(kayit));
    if (yigin.a == NULL) exit(1);

    /* komsuluk listesi + min-heap (anahtar = enaz) */
    heap_ekle(H, 0, 0);
    while (!heap_bos(H)) {
        u = heap_min_al(H);          /* O(log n) */
        if (secildi[u]) continue;    /* bayat kayit */
        secildi[u] = 1;
        for (p = baslik[u]; p; p = p->bag)
            if (!secildi[p->dugum] &&
                p->agirlik < enaz[p->dugum]) {
                enaz[p->dugum] = p->agirlik;
                yakin[p->dugum] = u;
                heap_ekle(H, p->dugum, p->agirlik);
            }
    }

    /* sunumda yok: agacin kenarlari ve bellek iadesi */
    for (v = 1; v < n; v++) {
        printf("(%d,%d) %d\n", yakin[v], v, enaz[v]);
        toplam += enaz[v];
    }
    printf("toplam = %d\n", toplam);
    free(yigin.a);
    for (v = 0; v < n; v++)
        while (baslik[v]) {
            p = baslik[v];
            baslik[v] = p->bag;
            free(p);
        }
    return 0;
}

/* Beklenen cikti:
 * (2,1) 16
 * (3,2) 12
 * (4,3) 22
 * (5,4) 25
 * (0,5) 10
 * (1,6) 14
 * toplam = 99
 */
