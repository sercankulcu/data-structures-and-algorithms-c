/* Bolme yontemi h(k) = k mod m ve carpma yontemi (Knuth, s = A * 2^32).
 * m = 10 iken 10'un katlari hep 0. kovaya duser; asal m = 11 onlari yayar.
 * Notlardaki ornekler: Tablo 14.3'teki sekiz anahtar m = 10 ve m = 11 ile;
 * CLRS ornegi k = 123456, p = 14 -> 67; ayrica k = 1..5, p = 4.
 * Slaytlar: "Bolme yontemi", "Carpma yontemi". */
#include <stdio.h>
#include <stdint.h>

unsigned h_bolme(unsigned k, unsigned m) { return k % m; }

/* w = 32 bit, m = 2^p; s = A * 2^32 */
uint32_t h_carpma(uint32_t k, int p) {
  const uint32_t s = 2654435769u;
  return (uint32_t)(k * s) >> (32 - p);
}

int main(void)
{
    unsigned k[] = {10, 20, 30, 40, 50, 60, 17, 27};
    printf("k       :");
    for (int i = 0; i < 8; i++) printf(" %2u", k[i]);
    printf("\nk mod 10:");
    for (int i = 0; i < 8; i++) printf(" %2u", h_bolme(k[i], 10));
    printf("\nk mod 11:");
    for (int i = 0; i < 8; i++) printf(" %2u", h_bolme(k[i], 11));
    printf("\n");

    printf("h_carpma(123456, 14) = %u\n", (unsigned) h_carpma(123456u, 14));
    printf("h_carpma(1..5, 4):");
    for (uint32_t x = 1; x <= 5; x++)
        printf(" %u", (unsigned) h_carpma(x, 4));
    printf("\n");
    return 0;
}

/* Beklenen cikti:
 * k       : 10 20 30 40 50 60 17 27
 * k mod 10:  0  0  0  0  0  0  7  7
 * k mod 11: 10  9  8  7  6  5  6  5
 * h_carpma(123456, 14) = 67
 * h_carpma(1..5, 4): 9 3 13 7 1
 */
