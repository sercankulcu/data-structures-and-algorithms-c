/* Sinav sorusu: oge yapisina int sayac alani eklenmistir. oge_say, alt
 * liste ogelerinin sayacina altindaki oge sayisini yazar ve toplam oge
 * sayisini dondurur. Sayaclar kok onde sirayla yazdirilir.
 * Slaytlar: "Sinav Sorusu: oge_say", "Sinav Sorusu: Dogrusal Form". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */

typedef enum { FALSE, TRUE } boolean;
typedef struct oge *oge_gost;
struct oge {
    boolean isaret;       // FALSE: atom
    union {
        char veri;        // atomik değer
        oge_gost L_bag;   // alt listenin başı
    };
    oge_gost bag;         // aynı düzeydeki sonraki
    int sayac;            /* soru metnindeki ek alan */
};

/* sunumda yok: oge ayiran yardimci */
oge_gost ogeal(void) {
    oge_gost p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "ogeal: bellek yetersiz\n");
        exit(EXIT_FAILURE);
    }
    p->sayac = 0;
    return p;
}

/* sunumda yok: dogrusal formdan liste kuran okuyucu (ders notundaki gibi) */
oge_gost ayristir(const char **s) {
    oge_gost bas = NULL, *son = &bas, q;
    (*s)++;                             // '(' atlanır
    while (**s != ')') {
        q = ogeal();
        if (**s == '(') {               // alt liste
            q->isaret = TRUE;
            q->L_bag = ayristir(s);
        } else {                        // atom
            q->isaret = FALSE;
            q->veri = **s;
            (*s)++;
        }
        q->bag = NULL;
        *son = q;                       // sona bağla
        son = &q->bag;
        if (**s == ',') (*s)++;         // ayırıcı atlanır
    }
    (*s)++;                             // ')' atlanır
    return bas;
}

/* sunumda yok: listeyi birakir */
void liste_bosalt(oge_gost L) {
    oge_gost q;
    while (L) {
        if (L->isaret)
            liste_bosalt(L->L_bag);
        q = L;
        L = L->bag;
        free(q);
    }
}

int oge_say(oge_gost L) {
    int miktar = 0;             // boş liste 0 öğe içerir
    for (; L; L = L->bag) {
        if (L->isaret) {        // alt liste var mı
            L->sayac = oge_say(L->L_bag);
            miktar += L->sayac; // alt listenin öğeleri de sayılır
        }
        miktar++;               // şu an gezilen öğe
    }
    return miktar;
}

void dogrusal_yaz(oge_gost L) {
    printf("(");
    for (; L; L = L->bag) {
        if (L->isaret) dogrusal_yaz(L->L_bag);
        else printf("%c", L->veri);
        if (L->bag) printf(",");
    }
    printf(")");
}

/* sunumda yok: alt liste ogelerinin sayaclarini kok onde sirayla yazar */
static void sayac_yaz(oge_gost L)
{
    for (; L; L = L->bag)
        if (L->isaret) {
            printf(" %d", L->sayac);
            sayac_yaz(L->L_bag);
        }
}

int main(void)
{
    const char *listeler[] = {
        "(a,(b,c))", "((a,b),((c,d),e))", "(())",
        "(d,(c,(e,(m,k),(()),z,y,(x,(r),b,a,()))))",
    };
    oge_gost L;
    const char *s;
    int i, n;

    for (i = 0; i < 4; i++) {
        s = listeler[i];
        L = ayristir(&s);
        n = oge_say(L);
        dogrusal_yaz(L);
        printf(" -> %d, sayaclar:", n);
        sayac_yaz(L);
        printf("\n");
        liste_bosalt(L);
    }
    return 0;
}

/* Beklenen cikti:
 * (a,(b,c)) -> 4, sayaclar: 2
 * ((a,b),((c,d),e)) -> 8, sayaclar: 2 4 2
 * (()) -> 1, sayaclar: 0
 * (d,(c,(e,(m,k),(()),z,y,(x,(r),b,a,())))) -> 19, sayaclar: 17 15 2 1 0 6 1 0
 */
