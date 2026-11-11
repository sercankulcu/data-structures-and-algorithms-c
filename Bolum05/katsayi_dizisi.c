/* Polinomun 1. gosterimi: katsayi dizisi. coef[i], x^i'nin katsayisidir;
 * sifir katsayilar da tutulur. Notlardaki ornek P(x) = 5x^100: 101 hucreden
 * yalniz biri anlamlidir ve yapi 408 bayt kaplar.
 * Slayt: "1. Yontem: Katsayi Dizisi". */
#include <stdio.h>

#define MAX_DEGREE 101   /* azami derece + 1 */
typedef struct {
  int degree;               /* en büyük üs */
  float coef[MAX_DEGREE];   /* coef[i]: x^i katsayısı */
} polynomial;
polynomial P;

int main(void)
{
    int i, sifir = 0;
    P.degree = 100;                       /* P global: coef[] sifirla baslar */
    P.coef[100] = 5;
    for (i = P.degree; i >= 0; i--) {
        if (P.coef[i] != 0) printf("%gx^%d\n", P.coef[i], i);
        else sifir++;
    }
    printf("sifir hucre: %d / %d\n", sifir, MAX_DEGREE);
    printf("sizeof(P) = %zu bayt\n", sizeof P);
    return 0;
}

/* Not: Linux x86-64: int ve float 4 bayt. */
/* Beklenen cikti:
 * 5x^100
 * sifir hucre: 100 / 101
 * sizeof(P) = 408 bayt
 */
