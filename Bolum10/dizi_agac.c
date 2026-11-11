/* Ikili agacin dizi ile gosterimi: dugumler 1'den baslayan gozlere konur;
 * ebeveyn i/2, sol cocuk 2i, sag cocuk 2i+1'dedir (indis n'yi asarsa
 * cocuk yoktur). Ornek: A-J harfleri 1-10 numarali gozlerde tam agac.
 * Slayt: "Dizi ile Gosterim". */
#include <stdio.h>

#define MAX_DUGUM 63   /* 2^k - 1 */
char agac[MAX_DUGUM + 1];  /* [0] kullanılmaz */
int  n;                    /* düğüm sayısı */

int baba(int i)     { return i / 2; }
int solcocuk(int i) { return 2 * i; }
int sagcocuk(int i) { return 2 * i + 1; }
/* çocuk var mı?  solcocuk(i) <= n */

/* sunumda yok: j numarali gozdeki dugum, yoksa '-' */
static char goz(int j)
{
    return (j >= 1 && j <= n) ? agac[j] : '-';
}

int main(void)
{
    const char *harfler = "ABCDEFGHIJ";
    int i;

    n = 10;
    for (i = 1; i <= n; i++)
        agac[i] = harfler[i - 1];

    printf(" i agac baba sol sag\n");
    for (i = 1; i <= n; i++)
        printf("%2d    %c    %c   %c   %c\n", i, agac[i],
               goz(baba(i)), goz(solcocuk(i)), goz(sagcocuk(i)));
    return 0;
}

/* Beklenen cikti:
 *  i agac baba sol sag
 *  1    A    -   B   C
 *  2    B    A   D   E
 *  3    C    A   F   G
 *  4    D    B   H   I
 *  5    E    B   J   -
 *  6    F    C   -   -
 *  7    G    C   -   -
 *  8    H    D   -   -
 *  9    I    D   -   -
 * 10    J    E   -   -
 */
