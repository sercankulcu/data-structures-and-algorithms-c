/* Kenarda aktivite (AoE) agi: ileri cozumleme topolojik sirada en erken olay
 * zamanlarini (en buyuk), ters cizgede geri cozumleme en gec zamanlari (en
 * kucuk) bulur; bollugu 0 olan aktiviteler kritiktir.
 * Notlardaki ornek: 9 olay, 11 aktivite (a0..a10); proje 18 gun,
 * EnErkenBas = 0 6 4 5 7 7 16 14 18, EnGecBas = 0 6 6 8 7 10 16 14 18,
 * kritik aktiviteler a0, a3, a6, a7, a9, a10.
 * Slaytlar: "En Erken Zaman: Formul", "En Erken Zamanlar Adim Adim" (ve
 * devami), "En Gec Zaman: Formul", "En Gec Zamanlar Adim Adim",
 * "Kritik Yol Hesabi (ek)". Yordam basliklari ders notundan. */
#include <stdio.h>
#include <stdlib.h>

#define MAX_DUGUM 10   /* sunumda yok: 9 olay icin (bolumdeki 6 yetmez) */

/* sunumda yok: ders notundaki sure alanli liste ogesi ve sayacli baslik */
typedef struct oge *oge_gost;
typedef struct oge {
    int dugum;
    int sure;            /* aktivitenin suresi */
    oge_gost bag;
} oge;
typedef struct {
    int sayac;
    oge_gost bag;
} basoge;
int EnErkenBas[MAX_DUGUM], EnGecBas[MAX_DUGUM];

/* sunumda yok: ders notundaki kenar_ekle (sona ekler, sayaci artirir) */
int kenar_ekle(basoge baslik[], int i, int j, int sure)
{
    oge_gost *son = &baslik[i].bag;
    oge_gost yeni = malloc(sizeof(oge));
    if (yeni == NULL)
        return 0;
    yeni->dugum = j;
    yeni->sure = sure;
    yeni->bag = NULL;
    while (*son != NULL)
        son = &(*son)->bag;
    *son = yeni;
    baslik[j].sayac++;
    return 1;
}

/* ileri cozumleme: TopolojikSira + en erken zaman satirlari */
void EnErkenHesapla(basoge baslik[], int n)
{
    int i, j, k, ust = -1;
    oge_gost p;
    for (i = 0; i < n; i++)
        EnErkenBas[i] = 0;
    for (i = 0; i < n; i++)
        if (!baslik[i].sayac) {
            baslik[i].sayac = ust;  ust = i; }
    for (i = 0; i < n; i++) {
        if (ust == -1) { printf("dongu"); break; }
        j = ust;  ust = baslik[ust].sayac;   /* yigindan al */
        printf("%d ", j);
        for (p = baslik[j].bag; p; p = p->bag) {
            k = p->dugum;
            if (EnErkenBas[k] < EnErkenBas[j] + p->sure)
                EnErkenBas[k] = EnErkenBas[j] + p->sure;
            if (--baslik[k].sayac == 0) {
                baslik[k].sayac = ust;  ust = k;  /* yigina */
            }
        }
    }
}

/* sunumda yok: ders notundaki ters_kur (oklari ters cevirir) */
int ters_kur(basoge baslik[], basoge ters[], int n)
{
    int i;
    oge_gost p;
    for (i = 0; i < n; i++) {
        ters[i].sayac = 0;
        ters[i].bag = NULL;
    }
    for (i = 0; i < n; i++)
        for (p = baslik[i].bag; p; p = p->bag)      /* <i, p->dugum> */
            if (!kenar_ekle(ters, p->dugum, i, p->sure))
                return 0;
    return 1;
}

/* geri cozumleme: ters cizgede ayni dongu, en gec zaman satirlari */
void EnGecHesapla(basoge baslik[], int n, int proje)
{
    int i, j, k, ust = -1;
    oge_gost p;
    for (i = 0; i < n; i++)
        EnGecBas[i] = proje;
    for (i = 0; i < n; i++)
        if (!baslik[i].sayac) {
            baslik[i].sayac = ust;  ust = i; }
    for (i = 0; i < n; i++) {
        if (ust == -1) { printf("dongu"); break; }
        j = ust;  ust = baslik[ust].sayac;   /* ters liste */
        printf("%d ", j);
        for (p = baslik[j].bag; p; p = p->bag) {
            k = p->dugum;                        /* k: oncul */
            if (EnGecBas[k] > EnGecBas[j] - p->sure)
                EnGecBas[k] = EnGecBas[j] - p->sure;
            if (--baslik[k].sayac == 0) {
                baslik[k].sayac = ust;  ust = k;
            }
        }
    }
}

void Bolluklar(basoge baslik[], int n)
{
    int i;
    oge_gost p;
    /* EnErkenBas[] ve EnGecBas[] hesaplandiktan sonra */
    for (i = 0; i < n; i++)
        for (p = baslik[i].bag; p; p = p->bag) {
            int erken = EnErkenBas[i];
            int gec   = EnGecBas[p->dugum] - p->sure;
            printf("<%d,%d> erken=%d gec=%d bolluk=%d%s\n",
                   i, p->dugum, erken, gec, gec - erken,
                   gec == erken ? " KRITIK" : "");
        }
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

/* sunumda yok: diziyi yazar */
static void dizi_yaz(const char *ad, const int a[], int n)
{
    int i;
    printf("%s =", ad);
    for (i = 0; i < n; i++) printf(" %d", a[i]);
    printf("\n");
}

int main(void)
{
    /* a0..a10: <kuyruk, bas, sure> */
    static const int akt[11][3] = {
        {0, 1, 6}, {0, 2, 4}, {0, 3, 5}, {1, 4, 1}, {2, 4, 1}, {3, 5, 2},
        {4, 6, 9}, {4, 7, 7}, {5, 7, 4}, {6, 8, 2}, {7, 8, 4}
    };
    static basoge baslik[MAX_DUGUM], ters[MAX_DUGUM];
    int n = 9, i;

    for (i = 0; i < 11; i++)
        if (!kenar_ekle(baslik, akt[i][0], akt[i][1], akt[i][2])) exit(1);
    if (!ters_kur(baslik, ters, n)) exit(1);   /* sayaclar bozulmadan once */

    printf("ileri: ");
    EnErkenHesapla(baslik, n);
    printf("\n");
    dizi_yaz("EnErkenBas", EnErkenBas, n);

    printf("geri: ");
    EnGecHesapla(ters, n, EnErkenBas[n - 1]);
    printf("\n");
    dizi_yaz("EnGecBas", EnGecBas, n);

    Bolluklar(baslik, n);
    listeleri_birak(baslik, n);
    listeleri_birak(ters, n);
    return 0;
}

/* Not: ileri/geri satirlarinin sonunda bir bosluk vardir. */
/* Beklenen cikti:
 * ileri: 0 3 5 2 1 4 7 6 8
 * EnErkenBas = 0 6 4 5 7 7 16 14 18
 * geri: 8 7 5 3 6 4 2 1 0
 * EnGecBas = 0 6 6 8 7 10 16 14 18
 * <0,1> erken=0 gec=0 bolluk=0 KRITIK
 * <0,2> erken=0 gec=2 bolluk=2
 * <0,3> erken=0 gec=3 bolluk=3
 * <1,4> erken=6 gec=6 bolluk=0 KRITIK
 * <2,4> erken=4 gec=6 bolluk=2
 * <3,5> erken=5 gec=8 bolluk=3
 * <4,6> erken=7 gec=7 bolluk=0 KRITIK
 * <4,7> erken=7 gec=7 bolluk=0 KRITIK
 * <5,7> erken=7 gec=10 bolluk=3
 * <6,8> erken=16 gec=16 bolluk=0 KRITIK
 * <7,8> erken=14 gec=14 bolluk=0 KRITIK
 */
