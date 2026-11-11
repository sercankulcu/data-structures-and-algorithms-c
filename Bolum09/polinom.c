/* Cok degiskenli polinomun genellestirilmis listeyle gosterimi: her duzey
 * bir VAR ogesiyle baslar; terimin katsayisi ya bir tamsayi (NO) ya da bir
 * alt polinom listesidir (PTR). Ornekler 3x^2y ve
 * P(x,y,z) = ((x^10+2x^8)y^3 + 3x^8y^2)z^2 + ((x^4+6x^3)y^4 + 2y)z;
 * degerleri x = 2, y = 3, z = 1 noktasinda hesaplanir.
 * Slayt: "Ornek: Cok Degiskenli Polinom". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */

typedef enum { VAR, PTR, NO } uclu_t;
typedef struct poge *poge_gost;
struct poge {
    uclu_t uclu;            // üçlü
    union {
        char deg;           // VAR: değişkenin adı
        poge_gost L_bag;    // PTR: katsayı bir liste
        int kat;            // NO : tamsayı katsayı
    };
    int us;                 // üs bilgisi
    poge_gost bag;
};

/* sunumda yok: polinomun degeri (ders notundaki gibi) */
// P: VAR öğesiyle başlayan liste; d['x'-'x'], d['y'-'x'], d['z'-'x']: değişken değerleri
long pdeger(poge_gost P, const long d[]) {
    long top = 0, v = d[P->deg - 'x'];  // bu düzeyin değişkeninin değeri
    long kat, kuv;
    int k;
    for (poge_gost p = P->bag; p; p = p->bag) {
        kat = (p->uclu == PTR) ? pdeger(p->L_bag, d)   // katsayı bir liste
                               : p->kat;               // NO: tamsayı
        for (kuv = 1, k = 0; k < p->us; k++) kuv *= v;
        top += kat * kuv;
    }
    return top;
}

/* sunumda yok: oge kuran, sayan ve birakan yardimcilar */
static poge_gost pyeni(uclu_t u, int us, poge_gost bag)
{
    poge_gost p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yok!\n");
        exit(EXIT_FAILURE);
    }
    p->uclu = u;
    p->us = us;
    p->bag = bag;
    return p;
}

static poge_gost yeni_var(char deg, poge_gost bag)
{
    poge_gost p = pyeni(VAR, 0, bag);
    p->deg = deg;
    return p;
}

static poge_gost yeni_no(int kat, int us, poge_gost bag)
{
    poge_gost p = pyeni(NO, us, bag);
    p->kat = kat;
    return p;
}

static poge_gost yeni_ptr(poge_gost alt, int us, poge_gost bag)
{
    poge_gost p = pyeni(PTR, us, bag);
    p->L_bag = alt;
    return p;
}

static int psay(poge_gost P)
{
    int s = 0;
    for (; P; P = P->bag)
        s += 1 + (P->uclu == PTR ? psay(P->L_bag) : 0);
    return s;
}

static void pbirak(poge_gost P)
{
    poge_gost q;
    while (P) {
        if (P->uclu == PTR) pbirak(P->L_bag);
        q = P->bag;
        free(P);
        P = q;
    }
}

int main(void)
{
    const long d[3] = { 2, 3, 1 };     /* x = 2, y = 3, z = 1 */
    poge_gost T, X1, X2, X3, Y1, Y2, P;

    /* 3x^2y = (3x^2) y^1 */
    T = yeni_var('y', yeni_ptr(yeni_var('x', yeni_no(3, 2, NULL)), 1, NULL));

    X1 = yeni_var('x', yeni_no(1, 10, yeni_no(2, 8, NULL)));   /* x^10 + 2x^8 */
    X2 = yeni_var('x', yeni_no(3, 8, NULL));                   /* 3x^8 */
    X3 = yeni_var('x', yeni_no(1, 4, yeni_no(6, 3, NULL)));    /* x^4 + 6x^3 */
    Y1 = yeni_var('y', yeni_ptr(X1, 3, yeni_ptr(X2, 2, NULL)));
    Y2 = yeni_var('y', yeni_ptr(X3, 4, yeni_no(2, 1, NULL)));
    P  = yeni_var('z', yeni_ptr(Y1, 2, yeni_ptr(Y2, 1, NULL)));

    printf("3x^2y: %d oge, deger = %ld\n", psay(T), pdeger(T, d));
    printf("P: %d oge\n", psay(P));
    printf("z^2 katsayisi = %ld\n", pdeger(Y1, d));
    printf("z katsayisi = %ld\n", pdeger(Y2, d));
    printf("P(2, 3, 1) = %ld\n", pdeger(P, d));

    pbirak(T);
    pbirak(P);
    return 0;
}

/* Beklenen cikti:
 * 3x^2y: 4 oge, deger = 36
 * P: 17 oge
 * z^2 katsayisi = 48384
 * z katsayisi = 5190
 * P(2, 3, 1) = 53574
 */
