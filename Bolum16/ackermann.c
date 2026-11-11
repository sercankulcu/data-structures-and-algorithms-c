/* Ackermann fonksiyonu: union-find'in O(m alfa(n)) sinirindaki ters
 * Ackermann'in kaynagi; cok hizli buyur. Ornek: ackermann(1, 2) = 4 ve
 * notlardaki A(m, n) tablosunun ilk dort satiri.
 * Slaytlar: "Sinav Sorusu", "Izleme: ackermann(1, 2)". */
#include <stdio.h>

unsigned long ackermann(unsigned long m,
                        unsigned long n) {
  if (m == 0) return n + 1;
  if (n == 0) return ackermann(m - 1, 1);
  return ackermann(m - 1, ackermann(m, n - 1));
}

int main(void)
{
    unsigned long m, n;
    printf("ackermann(1, 2) = %lu\n", ackermann(1, 2));
    for (m = 0; m <= 3; m++) {
        printf("A(%lu, n), n = 0..4:", m);
        for (n = 0; n <= 4; n++)
            printf(" %lu", ackermann(m, n));
        printf("\n");
    }
    return 0;
}

/* Beklenen cikti:
 * ackermann(1, 2) = 4
 * A(0, n), n = 0..4: 1 2 3 4 5
 * A(1, n), n = 0..4: 2 3 4 5 6
 * A(2, n), n = 0..4: 3 5 7 9 11
 * A(3, n), n = 0..4: 5 13 29 61 125
 */
