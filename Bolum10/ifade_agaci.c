/* Ifade agaci: yapraklarda sayi, ic dugumlerde islec durur. hesapla kok
 * sonda gezinmeyle once iki alt ifadeyi, sonra kokteki islemi hesaplar.
 * Ornekler: (8 / 4) * 3 + 5 ve A = 7, B = 3, C = 9, D = 4 icin (A + B) * (C - D).
 * Slaytlar: "Ifade Agaci Yapisi", "hesapla() Adim Adim". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */

typedef struct ifade *ifade_gost;
struct ifade {
    char      islec;   /* '+', '-', '*', '/' */
    int       deger;   /* yalnız yapraklarda */
    ifade_gost sol, sag;
};

int hesapla(ifade_gost t) {
  if (!t->sol && !t->sag)        /* yaprak: sayı */
    return t->deger;
  int a = hesapla(t->sol);
  int b = hesapla(t->sag);
  switch (t->islec) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    default:  return a / b;
  }
}

/* sunumda yok: agac kuran ve silen yardimcilar */
static ifade_gost yeni(char islec, int deger, ifade_gost sol, ifade_gost sag)
{
    ifade_gost p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yok!\n");
        exit(EXIT_FAILURE);
    }
    p->islec = islec;
    p->deger = deger;
    p->sol = sol;
    p->sag = sag;
    return p;
}

static ifade_gost sayi(int d) { return yeni(0, d, NULL, NULL); }
static ifade_gost isl(char c, ifade_gost sol, ifade_gost sag) { return yeni(c, 0, sol, sag); }

static void ifade_sil(ifade_gost t)
{
    if (t) {
        ifade_sil(t->sol);
        ifade_sil(t->sag);
        free(t);
    }
}

int main(void)
{
    ifade_gost t1 = isl('+', isl('*', isl('/', sayi(8), sayi(4)), sayi(3)), sayi(5));
    ifade_gost t2 = isl('*', isl('+', sayi(7), sayi(3)), isl('-', sayi(9), sayi(4)));

    printf("(8 / 4) * 3 + 5 = %d\n", hesapla(t1));
    printf("(7 + 3) * (9 - 4) = %d\n", hesapla(t2));
    ifade_sil(t1);
    ifade_sil(t2);
    return 0;
}

/* Beklenen cikti:
 * (8 / 4) * 3 + 5 = 11
 * (7 + 3) * (9 - 4) = 50
 */
