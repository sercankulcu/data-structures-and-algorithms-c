/* Listenin bagli gerceklenmesi: bl_ekle isaretciye isaretci (pp) ile
 * degisecek bagin adresini tutar; basa ve araya ekleme ayni koddur.
 * Ornek: 7, 4, 2 sirasiyla 0., 0. ve 2. konumlara eklenir (4 7 2), sonra
 * 1. konuma 9 eklenir; 6 ve -1 konumlari reddedilir.
 * Slayt: "Bagli Gercekleme". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free */
#include <stdbool.h>  /* sunumda yok: bool */

typedef struct dugum *dugum_gost;
struct dugum { int deger; dugum_gost bag; };
typedef struct { dugum_gost bas; int n; } BListe;

bool bl_ekle(BListe *L, int i, int x) {
    dugum_gost *pp = &L->bas, yeni;
    if (i < 0 || i > L->n) return false;
    while (i-- > 0)
        pp = &(*pp)->bag;        // i. bağa yürü
    yeni = malloc(sizeof *yeni);
    if (yeni == NULL) return false;
    yeni->deger = x;
    yeni->bag = *pp;
    *pp = yeni;                  // baş ya da ara: aynı
    L->n++;
    return true;
}

/* sunumda yok: listeyi yazar */
static void yaz(const BListe *L)
{
    dugum_gost p;
    for (p = L->bas; p; p = p->bag)
        printf(p == L->bas ? "%d" : " -> %d", p->deger);
    printf(" (n = %d)\n", L->n);
}

/* sunumda yok: dugumleri geri verir */
static void bl_bosalt(BListe *L)
{
    dugum_gost p, q;
    for (p = L->bas; p; p = q) { q = p->bag; free(p); }
    L->bas = NULL;
    L->n = 0;
}

int main(void)
{
    BListe B = { NULL, 0 };

    bl_ekle(&B, 0, 7);
    bl_ekle(&B, 0, 4);
    bl_ekle(&B, 2, 2);
    yaz(&B);
    printf("bl_ekle(&B, 1, 9) = %d\n", bl_ekle(&B, 1, 9));
    yaz(&B);
    printf("bl_ekle(&B, 6, 5) = %d\n", bl_ekle(&B, 6, 5));
    printf("bl_ekle(&B, -1, 5) = %d\n", bl_ekle(&B, -1, 5));
    bl_bosalt(&B);
    return 0;
}

/* Beklenen cikti:
 * 4 -> 7 -> 2 (n = 3)
 * bl_ekle(&B, 1, 9) = 1
 * 4 -> 9 -> 7 -> 2 (n = 4)
 * bl_ekle(&B, 6, 5) = 0
 * bl_ekle(&B, -1, 5) = 0
 */
