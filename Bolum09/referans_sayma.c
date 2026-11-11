/* Paylasimli listeler ve referans sayma: her liste bir baslik dugumuyle
 * baslar, baslikta listeyi gosteren isaretci sayisi (sayac) tutulur.
 * Ornek: A = (a,(b,c)), B = (A, A, ()). A'nin sayaci 3 (A degiskeni ve
 * B'nin iki ogesi). liste_birak(&B) A'yi birakmaz, yalniz sayacini 1'e
 * indirir; liste_birak(&A) A'yi birakir.
 * Slayt: "Paylasim ve Referans Sayma". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */

/* sunumda yok: baslik dugumunde sayac alani olan oge yapisi */
typedef enum { FALSE, TRUE } boolean;
typedef struct oge *oge_gost;
struct oge {
    boolean isaret;       // FALSE: atom
    union {
        char veri;        // atomik değer
        oge_gost L_bag;   // alt listenin başlığı
    };
    oge_gost bag;         // aynı düzeydeki sonraki
    int sayac;            // yalnız başlıkta: gösteren sayısı
};

// başlıkta sayac: bu listeyi gösteren sayısı
void liste_birak(oge_gost *L) {
    oge_gost p, q;
    if (*L == NULL) return;
    if (--(*L)->sayac > 0) {    // başkası kullanıyor
        *L = NULL; return;
    }
    p = (*L)->bag;              // ilk gerçek öğe
    free(*L);
    while (p) {
        if (p->isaret) liste_birak(&p->L_bag);
        q = p; p = p->bag; free(q);
    }
    *L = NULL;
}

/* sunumda yok: oge kuran ve yazan yardimcilar */
static oge_gost yeni(boolean isaret, oge_gost bag)
{
    oge_gost p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yok!\n");
        exit(EXIT_FAILURE);
    }
    p->isaret = isaret;
    p->bag = bag;
    p->sayac = 0;
    return p;
}

static oge_gost baslik(int sayac, oge_gost ilk)
{
    oge_gost h = yeni(FALSE, ilk);
    h->veri = '#';
    h->sayac = sayac;
    return h;
}

static oge_gost atom(char c, oge_gost bag)
{
    oge_gost p = yeni(FALSE, bag);
    p->veri = c;
    return p;
}

static oge_gost alt(oge_gost liste, oge_gost bag)   /* liste: bir baslik */
{
    oge_gost p = yeni(TRUE, bag);
    p->L_bag = liste;
    return p;
}

static void hyaz(oge_gost h)            /* baslikli listeyi yazar */
{
    printf("(");
    for (oge_gost p = h->bag; p; p = p->bag) {
        if (p->isaret) hyaz(p->L_bag);
        else printf("%c", p->veri);
        if (p->bag) printf(",");
    }
    printf(")");
}

int main(void)
{
    oge_gost A, B, bc, bos;

    bc = baslik(1, atom('b', atom('c', NULL)));
    A = baslik(1, atom('a', alt(bc, NULL)));
    bos = baslik(1, NULL);
    B = baslik(1, alt(A, alt(A, alt(bos, NULL))));
    A->sayac += 2;                      /* B'nin iki ogesi de A'yi gosterir */

    printf("A = ");
    hyaz(A);
    printf(", sayac = %d\n", A->sayac);
    printf("B = ");
    hyaz(B);
    printf(", sayac = %d\n", B->sayac);

    liste_birak(&B);
    printf("liste_birak(&B): B %s, A sayaci = %d\n",
           B == NULL ? "NULL" : "NULL degil", A->sayac);
    liste_birak(&A);
    printf("liste_birak(&A): A %s\n", A == NULL ? "NULL" : "NULL degil");
    return 0;
}

/* Beklenen cikti:
 * A = (a,(b,c)), sayac = 3
 * B = ((a,(b,c)),(a,(b,c)),()), sayac = 1
 * liste_birak(&B): B NULL, A sayaci = 1
 * liste_birak(&A): A NULL
 */
