/* Genel agactan ikili agaca: sol cocuk - sag kardes gosterimi. Her dugum
 * ilk cocugunu ve sagindaki kardesini gosterir; yapi ikili agac dugumuyle
 * aynidir. Ornek agac A(B(E(K,L),F),C(G),D(H(M),I,J)). Ikili agacin kok
 * onde sirasi genel agacin kok onde sirasina, kok ortada sirasi genel
 * agacin kok sonda sirasina esittir.
 * Slayt: "Genel Agactan Ikili Agaca". */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: malloc, free, exit */

struct gdugum {
    char veri;
    struct gdugum *ilk_cocuk;  /* = sol */
    struct gdugum *kardes;     /* = sağ */
};

/* sunumda yok: dugum kurma, gezinme ve silme */
static struct gdugum *g(char veri, struct gdugum *ilk_cocuk, struct gdugum *kardes)
{
    struct gdugum *p = malloc(sizeof *p);
    if (p == NULL) {
        fprintf(stderr, "Bellek yok!\n");
        exit(EXIT_FAILURE);
    }
    p->veri = veri;
    p->ilk_cocuk = ilk_cocuk;
    p->kardes = kardes;
    return p;
}

static void kok_onde(const struct gdugum *L)     /* ikili agac gibi: V-sol-sag */
{
    if (L) {
        printf("%c", L->veri);
        kok_onde(L->ilk_cocuk);
        kok_onde(L->kardes);
    }
}

static void kok_ortada(const struct gdugum *L)   /* ikili agac gibi: sol-V-sag */
{
    if (L) {
        kok_ortada(L->ilk_cocuk);
        printf("%c", L->veri);
        kok_ortada(L->kardes);
    }
}

static void gsil(struct gdugum *L)
{
    if (L) {
        gsil(L->ilk_cocuk);
        gsil(L->kardes);
        free(L);
    }
}

int main(void)
{
    struct gdugum *D, *C, *B, *A;

    D = g('D', g('H', g('M', NULL, NULL), g('I', NULL, g('J', NULL, NULL))), NULL);
    C = g('C', g('G', NULL, NULL), D);
    B = g('B', g('E', g('K', NULL, g('L', NULL, NULL)), g('F', NULL, NULL)), C);
    A = g('A', B, NULL);                 /* kokun kardesi yok: sag bag NULL */

    printf("kok onde  : ");
    kok_onde(A);
    printf("\nkok ortada: ");
    kok_ortada(A);
    printf("\n");
    gsil(A);
    return 0;
}

/* Beklenen cikti:
 * kok onde  : ABEKLFCGDHMIJ
 * kok ortada: KLEFBGCMHIJDA
 */
