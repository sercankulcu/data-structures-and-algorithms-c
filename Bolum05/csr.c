/* Sikistirilmis satir gosterimi (CSR) ile matris-vektor carpimi y = M * x.
 * val ve col_ind dolu ogeleri satir sirasiyla tutar; i. satir
 * val[row_ptr[i] .. row_ptr[i+1]-1] araligidir. Bos satir (3. satir) iki
 * esit row_ptr degeriyle gorunur.
 * Notlardaki ornek: 6 x 6 ornek matris ve x = (1, 2, 3, 4, 5, 6).
 * Slayt: "CSR Gosterimi". */
#include <stdio.h>

int main(void)
{
    /* sunumda yok: notlardaki 6 x 6 matrisin CSR dizileri */
    int val[]     = {15, 22, -15, 11, 3, -6, 91, 28};
    int col_ind[] = { 0,  3,   5,  1, 2,  3,  0,  2};
    int row_ptr[] = {0, 3, 5, 6, 6, 7, 8};
    int x[] = {1, 2, 3, 4, 5, 6};
    int y[6];
    int rows = 6, i, k;

    /* y = M * x  (matris-vektör çarpımı) */
    for (i = 0; i < rows; i++) {
      y[i] = 0;
      for (k = row_ptr[i]; k < row_ptr[i+1]; k++)
        y[i] += val[k] * x[col_ind[k]];
    }

    printf("y =");                          /* sunumda yok */
    for (i = 0; i < rows; i++) printf(" %d", y[i]);
    printf("\n");
    return 0;
}

/* Beklenen cikti:
 * y = 13 31 -24 0 91 84
 */
