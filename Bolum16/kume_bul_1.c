/* Ebeveyn (ata) dizisiyle ayrik kumeler, ilk surum: Kume_Bul_1 koke kadar
 * yurur, Birlesim_1 tek atamayla bir koku otekinin altina baglar.
 * 1) Notlardaki orman: ata = {-1, 4, -1, 2, -1, 2, 0, 0, 0, 4};
 *    Kume_Bul_1(9), Birlesim_1(4, 0), yeniden Kume_Bul_1(9).
 * 2) Kotu islem dizisi (n = 5): Birlesim_1(0,1) ... Birlesim_1(3,4) zincir
 *    kurar; Kume_Bul_1(i) n - 1 - i ilerleme yapar, toplam n(n-1)/2.
 * Slaytlar: "ata dizisi", "Kume_Bul_1 ve Birlesim_1",
 * "Izleme: Kume_Bul_1 / Birlesim_1", "Izleme: kotu islem dizisi", "Analiz". */
#include <stdio.h>

#define N 10
int ata[N] = { -1, 4, -1, 2, -1, 2, 0, 0, 0, 4 };

int Kume_Bul_1(int i) {
  for (; ata[i] >= 0; i = ata[i])
    ;                /* negatife dek ilerle */
  return i;
}
void Birlesim_1(int i, int j) {
  ata[i] = j;        /* i kümesini j'ye bağla */
}

/* sunumda yok: kokun uzakligini (ilerleme sayisini) sayar */
static int derinlik(int i)
{
    int d = 0;
    for (; ata[i] >= 0; i = ata[i])
        d++;
    return d;
}

/* sunumda yok: diziyi yazar */
static void ata_yaz(int n)
{
    int i;
    printf("ata =");
    for (i = 0; i < n; i++) printf(" %d", ata[i]);
    printf("\n");
}

int main(void)
{
    int i, n = 5, toplam = 0;

    printf("Kume_Bul_1(9) = %d\n", Kume_Bul_1(9));
    Birlesim_1(4, 0);
    printf("Birlesim_1(4, 0) sonrasi ");
    ata_yaz(N);
    printf("Kume_Bul_1(9) = %d\n", Kume_Bul_1(9));

    /* Analiz: n tek ogeli kumeyle basla */
    for (i = 0; i < n; i++) ata[i] = -1;
    for (i = 0; i < n - 1; i++)
        Birlesim_1(i, i + 1);
    printf("zincir: ");
    ata_yaz(n);
    for (i = 0; i < n; i++) {
        printf("Kume_Bul_1(%d) = %d, ilerleme = %d\n",
               i, Kume_Bul_1(i), derinlik(i));
        toplam += derinlik(i);
    }
    printf("toplam ilerleme = %d\n", toplam);
    return 0;
}

/* Beklenen cikti:
 * Kume_Bul_1(9) = 4
 * Birlesim_1(4, 0) sonrasi ata = -1 4 -1 2 0 2 0 0 0 4
 * Kume_Bul_1(9) = 0
 * zincir: ata = 1 2 3 4 -1
 * Kume_Bul_1(0) = 4, ilerleme = 4
 * Kume_Bul_1(1) = 4, ilerleme = 3
 * Kume_Bul_1(2) = 4, ilerleme = 2
 * Kume_Bul_1(3) = 4, ilerleme = 1
 * Kume_Bul_1(4) = 4, ilerleme = 0
 * toplam ilerleme = 10
 */
