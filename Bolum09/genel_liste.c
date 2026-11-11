/* Genellestirilmis listeler: atom/alt liste etiketli oge yapisi ve temel
 * ozyinelemeli yordamlar. Listeler dogrusal formdan (ornegin "(a,(b,c))")
 * okunur, dogrusal_yaz ile geri yazilir. Gosterilenler: kopyala, esitmi,
 * esit, dolas_yaz, derinlik (ozyinelemeli), derinlik_d (yerel yiginla),
 * devrik_al (her duzeyi ters cevirir), agac_yaz (agac notasyonu).
 * Slaytlar: "Bellek Gorunumu", "Soru: Kopyalama", "Kopyalama Adim Adim",
 * "Soru: Esitlik", "Esitlik Adim Adim", "Direnc Noktasi",
 * "Soru: Gezip Yazdirma", "Gezinme Adim Adim", "Soru: Derinlik
 * (Ozyinelemeli)", "Derinlik Adim Adim", "Ornek Cozum (Yinelemeli)",
 * "Dogru Yinelemeli Cozum", "Soru: Ters Cevirme", "Ters Cevirme Adim Adim",
 * "Odevler", "Sinav Sorusu: Dogrusal Form". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */
#include <stdbool.h>  /* sunumda yok: esit icin bool */

typedef enum { FALSE, TRUE } boolean;
typedef struct oge *oge_gost;
struct oge {
    boolean isaret;       // FALSE: atom
    union {
        char veri;        // atomik değer
        oge_gost L_bag;   // alt listenin başı
    };
    oge_gost bag;         // aynı düzeydeki sonraki
};

/* sunumda yok: oge ayiran yardimci (ders notundaki gibi) */
oge_gost ogeal(void) {
    oge_gost p = malloc(sizeof *p);
    if (p == NULL) {                    // bellek kalmadı
        fprintf(stderr, "ogeal: bellek yetersiz\n");
        exit(EXIT_FAILURE);
    }
    return p;                           // alanlar ilklendirilmedi
}

/* sunumda yok: dogrusal formdan liste kuran okuyucu (ders notundaki gibi) */
// *s, '(' karakterini gösterirken çağrılır; liste kurulunca
// *s, eşleşen ')' karakterinin bir sonrasını gösterir.
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

/* sunumda yok: paylasimsiz listeyi birakir (ders notundaki gibi) */
void liste_bosalt(oge_gost L) {
    oge_gost q;
    while (L) {
        if (L->isaret)
            liste_bosalt(L->L_bag);     // önce alt liste
        q = L;
        L = L->bag;                     // bağ, free'den önce okunur
        free(q);
    }
}

/* "Sinav Sorusu: Dogrusal Form" */
void dogrusal_yaz(oge_gost L) {
    printf("(");
    for (; L; L = L->bag) {
        if (L->isaret) dogrusal_yaz(L->L_bag);
        else printf("%c", L->veri);
        if (L->bag) printf(",");
    }
    printf(")");
}

/* "Soru: Kopyalama" */
oge_gost kopyala(oge_gost L) {
    oge_gost q = NULL;
    if (L) {                    // L NULL değil mi
        q = ogeal();            // bir öğe al
        q->isaret = L->isaret;
        if (!L->isaret) q->veri = L->veri; // atom
        else q->L_bag = kopyala(L->L_bag);
        q->bag = kopyala(L->bag);
    }
    return q;
}

/* "Soru: Esitlik" */
boolean esitmi(oge_gost T, oge_gost L) {
    boolean x = TRUE;
    if (!T && !L) return TRUE;
    if (T && L && T->isaret == L->isaret) {
        if (!T->isaret)         // atomik mi?
            x = (T->veri == L->veri) ? TRUE : FALSE;
        else                    // alt listeler
            x = esitmi(T->L_bag, L->L_bag);
        if (x == TRUE) return esitmi(T->bag, L->bag);
    }
    return FALSE;
}

/* "Direnc Noktasi" */
bool esit(oge_gost T, oge_gost L) {
    if (T == L) return true;        // aynı düğüm/ikisi NULL
    if (!T || !L || T->isaret != L->isaret) return false;
    if (T->isaret ? !esit(T->L_bag, L->L_bag)
                  : T->veri != L->veri)
        return false;
    return esit(T->bag, L->bag);
}

/* "Soru: Gezip Yazdirma" slaytindaki ilk yazim hatalidir, calistirilmaz:
 * cagrilar tanimsiz dolas'i gosterir (derlenmez) ve if (L)'den sonra
 * suslu parantez olmadigi icin son satir L == NULL iken de calisir.
 *
 * void dolas_yaz( oge_gost L ){
 *     if(L)
 *         if(!L->isaret)
 *             printf("%c", L->veri);
 *         else
 *             dolas(L->L_bag);
 *         dolas( L->bag );
 * }
 *
 * Dogru yazim: */
void dolas_yaz(oge_gost L) {
    if (L) {
        if (!L->isaret)
            printf("%c", L->veri); // atomikse yaz
        else
            dolas_yaz(L->L_bag);
        dolas_yaz(L->bag);
    }
}

/* "Soru: Derinlik (Ozyinelemeli)" */
int derinlik(oge_gost L) {
    oge_gost p = L;  int m = 0;    // m: en büyük
    if (!L) return 0;
    while (p) {
        if (p->isaret) {
            int n = derinlik(p->L_bag);
            if (m < n) m = n;
        }
        p = p->bag;
    }
    return m + 1;
}

/* "Ornek Cozum (Yinelemeli)" slaytindaki sinav cevabi hatalidir ve
 * derlenmez (p int olarak bildirilir, for'un ucuncu kismi p'yi
 * ilerletmez, kuresel yigina dayanir); yalniz yorum olarak:
 *
 * int derinlik( agac_gost L ){
 *     agac_gost yigit_al(); void yigit_ekle(agac_gost);
 *     int max = 0;
 *     for( int current = 1, p = L ; p ; p->bag ){
 *         if( p->isaret ){ // alt listeye gir
 *             yigit_ekle(p);
 *             p = p -> L_bag;
 *             current++;
 *         }
 *         if( !p->bag ){   // liste sonu, üste çık
 *             p = yigit_al();
 *             if( max < current ) max = current;
 *             current--;
 *         }
 *     }
 *     return max;
 * }
 *
 * "Dogru Yinelemeli Cozum": */
int derinlik_d(oge_gost L) {
    oge_gost yigit[100];       // yerel yığın (derinlik<100)
    int ust = 0, d = 1, m = 0;
    oge_gost p = L;
    if (!L) return 0;
    for (;;) {
        if (p == NULL) {             // düzey bitti
            if (ust == 0) return m;
            p = yigit[--ust]->bag;   // T'den sonraki
            d--;
        } else {
            if (d > m) m = d;
            if (p->isaret && p->L_bag) {
                yigit[ust++] = p;    // alt listeye in
                p = p->L_bag;
                d++;
            } else p = p->bag;
        }
    }
}

/* "Soru: Ters Cevirme" */
void devrik_al(oge_gost *L) {
    oge_gost r, p = *L, q = NULL;
    while (p) {
        if (p->isaret)              // atomik değilse
            devrik_al(&p->L_bag);
        r = q;
        q = p;
        p = p->bag;
        q->bag = r;
    }
    *L = q;
}

/* "Odevler" */
void agac_yaz(oge_gost L) {   // L: (kök, alt ağaçlar...)
    printf("%c", L->veri);          // kök etiketi
    if (L->bag) {
        printf("(");
        for (oge_gost p = L->bag; p; p = p->bag) {
            if (p->isaret) agac_yaz(p->L_bag);
            else printf("%c", p->veri);   // yaprak
            if (p->bag) printf(",");
        }
        printf(")");
    }
}

/* sunumda yok: metinden liste kurar */
static oge_gost oku(const char *metin)
{
    const char *s = metin;
    return ayristir(&s);
}

int main(void)
{
    const char *derin[] = {
        "(a,b)", "(a,(b,c))", "(a,(b,(c)))", "(())", "()", "((()))",
        "(d,(c,(e,(m,k),(()),z,y,(x,(r),b,a,()))))",
    };
    const char *devrik[] = { "(a,(b,c))", "((a,b),((c,d),e))", "(a,(()),b)" };
    const char *agaclar[] = {
        "(A,(B,(E,K,L),F),(C,G),(D,(H,M),I,J))",
        "(A,(B,(E,H,(I,J,K)),F),(C,G),D)",
    };
    oge_gost L, K, T, U;
    int i;

    /* kopyala */
    L = oku("((a,b),((c,d),e))");
    K = kopyala(L);
    printf("L = ");
    dogrusal_yaz(L);
    printf("\nkopyala(L) = ");
    dogrusal_yaz(K);
    printf("\nesitmi(L, kopya) = %d, esit(L, kopya) = %d\n",
           esitmi(L, K), esit(L, K));
    liste_bosalt(L);
    liste_bosalt(K);

    /* esitmi ve esit */
    T = oku("(a,(b,c))");
    U = oku("(a,(b,d))");
    printf("esitmi((a,(b,c)), (a,(b,d))) = %d, esit = %d\n",
           esitmi(T, U), esit(T, U));
    printf("esitmi((), ()) = %d, esit = %d\n",
           esitmi(NULL, NULL), esit(NULL, NULL));
    liste_bosalt(T);
    liste_bosalt(U);

    /* dolas_yaz */
    L = oku("(a,(b),c)");
    printf("dolas_yaz((a,(b),c)): ");
    dolas_yaz(L);
    printf("\n");
    liste_bosalt(L);
    L = oku(agaclar[0]);
    printf("dolas_yaz(agac listesi): ");
    dolas_yaz(L);
    printf("\n");
    liste_bosalt(L);

    /* derinlik ve derinlik_d */
    for (i = 0; i < 7; i++) {
        L = oku(derin[i]);
        printf("derinlik %s = %d, derinlik_d = %d\n",
               derin[i], derinlik(L), derinlik_d(L));
        liste_bosalt(L);
    }

    /* devrik_al */
    for (i = 0; i < 3; i++) {
        L = oku(devrik[i]);
        devrik_al(&L);
        printf("devrik_al %s -> ", devrik[i]);
        dogrusal_yaz(L);
        printf("\n");
        liste_bosalt(L);
    }

    /* agac_yaz */
    for (i = 0; i < 2; i++) {
        L = oku(agaclar[i]);
        printf("agac_yaz: ");
        agac_yaz(L);
        printf("\n");
        liste_bosalt(L);
    }
    return 0;
}

/* Beklenen cikti:
 * L = ((a,b),((c,d),e))
 * kopyala(L) = ((a,b),((c,d),e))
 * esitmi(L, kopya) = 1, esit(L, kopya) = 1
 * esitmi((a,(b,c)), (a,(b,d))) = 0, esit = 0
 * esitmi((), ()) = 1, esit = 1
 * dolas_yaz((a,(b),c)): abc
 * dolas_yaz(agac listesi): ABEKLFCGDHMIJ
 * derinlik (a,b) = 1, derinlik_d = 1
 * derinlik (a,(b,c)) = 2, derinlik_d = 2
 * derinlik (a,(b,(c))) = 3, derinlik_d = 3
 * derinlik (()) = 1, derinlik_d = 1
 * derinlik () = 0, derinlik_d = 0
 * derinlik ((())) = 2, derinlik_d = 2
 * derinlik (d,(c,(e,(m,k),(()),z,y,(x,(r),b,a,())))) = 5, derinlik_d = 5
 * devrik_al (a,(b,c)) -> ((c,b),a)
 * devrik_al ((a,b),((c,d),e)) -> ((e,(d,c)),(b,a))
 * devrik_al (a,(()),b) -> (b,(()),a)
 * agac_yaz: A(B(E(K,L),F),C(G),D(H(M),I,J))
 * agac_yaz: A(B(E(H,I(J,K)),F),C(G),D)
 */
