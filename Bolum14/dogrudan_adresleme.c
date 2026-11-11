/* Dogrudan adresleme: anahtar dogrudan dizinin indisidir; T[k].var gozun
 * dolu olup olmadigini soyler. Global dizi sifirla basladigi icin tablo bos
 * baslar.
 * Notlardaki ornek: 2, 3, 5, 8 numarali gozlere Ali, Can, Ece, Naz yazilir;
 * 0..9 arasindaki her anahtar aranir.
 * Slayt: "Dogrudan adresleme". */
#include <stdio.h>
#include <stddef.h>


typedef struct { int var; char ad[16]; } kayit;
kayit T[10];               /* anahtar = indis */

kayit *da_ara(int k) {
  return T[k].var ? &T[k] : NULL;
}

/* sunumda yok: ekleme T[k].var = 1 yapip veriyi yazar */
static void da_ekle(int k, const char *ad) {
    T[k].var = 1;
    snprintf(T[k].ad, sizeof T[k].ad, "%s", ad);
}

int main(void)
{
    da_ekle(2, "Ali");
    da_ekle(3, "Can");
    da_ekle(5, "Ece");
    da_ekle(8, "Naz");
    for (int k = 0; k < 10; k++) {
        kayit *p = da_ara(k);
        printf("da_ara(%d) = %s\n", k, p ? p->ad : "NULL");
    }
    return 0;
}

/* Beklenen cikti:
 * da_ara(0) = NULL
 * da_ara(1) = NULL
 * da_ara(2) = Ali
 * da_ara(3) = Can
 * da_ara(4) = NULL
 * da_ara(5) = Ece
 * da_ara(6) = NULL
 * da_ara(7) = NULL
 * da_ara(8) = Naz
 * da_ara(9) = NULL
 */
