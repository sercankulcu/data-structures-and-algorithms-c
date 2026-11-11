/* Cok bagli liste (adjacency multilist): yonsuz cizgenin her kenari tek bir
 * ogedir ve iki ucunun listesinde birden bulunur. ml_ekle kenari iki listenin
 * basina ekler; komsulari_yaz v'nin hangi uc oldugunu sinayip dogru bagi izler.
 * Notlardaki ornek: G1'in kenarlari (0,1), (0,2), (0,3), (1,2), (1,3), (2,3)
 * bu sirayla ml_ekle ile eklenir; komsulari_yaz(2) "3 1 0" yazar.
 * Slaytlar: "Cok Bagli Liste", "Cok Bagli Listede Gezinme",
 * "Cok Bagli Listeye Ekleme". */
#include <stdio.h>
#include <stdlib.h>

#define MAX_DUGUM 50   /* sunumda yok: "Komsuluk Listesi" slaytindaki sabit */

typedef struct kenar *kenar_gost;
typedef struct kenar {
    short isaret;        /* islendi mi */
    int dugum1, dugum2;  /* uclar */
    kenar_gost list1;    /* dugum1 sonraki */
    kenar_gost list2;    /* dugum2 sonraki */
} kenar;
kenar_gost baslik[MAX_DUGUM];

void komsulari_yaz(int v)
{
    kenar_gost p = baslik[v];
    while (p) {
        if (p->dugum1 == v) {       /* v: dugum1 */
            printf("%d ", p->dugum2);  p = p->list1;
        } else {                    /* v: dugum2 */
            printf("%d ", p->dugum1);  p = p->list2;
        }
    }
}

void ml_ekle(int u, int v)
{
    kenar_gost p = malloc(sizeof(kenar));
    if (p == NULL) exit(1);
    p->isaret = 0;
    p->dugum1 = u;  p->dugum2 = v;
    p->list1 = baslik[u];  /* u listesine */
    p->list2 = baslik[v];  /* v listesine */
    baslik[u] = baslik[v] = p;  /* ikisine de basa */
}

/* sunumda yok: her kenar iki listede oldugundan once dugum1 tarafindan bir kez
 * toplanir, sonra hepsi birakilir */
static void kenarlari_birak(int n)
{
    kenar_gost hepsi[64];
    int say = 0, v, i;
    kenar_gost p;
    for (v = 0; v < n; v++) {
        p = baslik[v];
        while (p) {
            if (p->dugum1 == v) {
                hepsi[say++] = p;  p = p->list1;
            } else {
                p = p->list2;
            }
        }
    }
    for (i = 0; i < say; i++) free(hepsi[i]);
    for (v = 0; v < n; v++) baslik[v] = NULL;
}

int main(void)
{
    int v;
    ml_ekle(0, 1);  ml_ekle(0, 2);  ml_ekle(0, 3);
    ml_ekle(1, 2);  ml_ekle(1, 3);  ml_ekle(2, 3);
    for (v = 0; v < 4; v++) {
        printf("komsulari_yaz(%d): ", v);
        komsulari_yaz(v);
        printf("\n");
    }
    kenarlari_birak(4);
    return 0;
}

/* Not: her sayidan sonra bir bosluk vardir. */
/* Beklenen cikti:
 * komsulari_yaz(0): 3 2 1
 * komsulari_yaz(1): 3 2 0
 * komsulari_yaz(2): 3 1 0
 * komsulari_yaz(3): 2 1 0
 */
