/* Azaltma kurali (yol kisaltma, Kume_Bul_2): once kok bulunur, sonra yoldaki
 * her dugum dogrudan koke baglanir.
 * Notlardaki ornek: agirlikli izlemenin sonundaki agac
 * ata = {-8, 0, 0, 2, 0, 4, 4, 6}; sirayla Kume_Bul_2(7), Kume_Bul_2(7),
 * Kume_Bul_2(5).
 * Slaytlar: "Kume_Bul_2", "Izleme: Kume_Bul_2(7)",
 * "Izleme: Kume_Bul_2 (devam)". */
#include <stdio.h>

#define N 10   /* sunumda yok: "ata dizisi" slaytindaki boyut */
int ata[N] = { -8, 0, 0, 2, 0, 4, 4, 6 };   /* sunumda yok: ornek agac */

int Kume_Bul_2(int i) {
  int r, s;
  for (r = i; ata[r] >= 0; r = ata[r])
    ;                   /* kökü bul */
  while (i != r) {      /* yolu azalt */
    s = ata[i];         /* i'nin ebeveynini sakla */
    ata[i] = r;         /* i'yi doğrudan köke bağla */
    i = s;              /* ebeveynine geç */
  }
  return r;
}

/* sunumda yok: ilk 8 hucreyi yazar */
static void ata_yaz(void)
{
    int i;
    printf("  ata =");
    for (i = 0; i < 8; i++) printf(" %d", ata[i]);
    printf("\n");
}

int main(void)
{
    printf("Kume_Bul_2(7) = %d\n", Kume_Bul_2(7));
    ata_yaz();
    printf("Kume_Bul_2(7) = %d\n", Kume_Bul_2(7));
    ata_yaz();
    printf("Kume_Bul_2(5) = %d\n", Kume_Bul_2(5));
    ata_yaz();
    return 0;
}

/* Beklenen cikti:
 * Kume_Bul_2(7) = 0
 *   ata = -8 0 0 2 0 4 0 0
 * Kume_Bul_2(7) = 0
 *   ata = -8 0 0 2 0 4 0 0
 * Kume_Bul_2(5) = 0
 *   ata = -8 0 0 2 0 0 0 0
 */
