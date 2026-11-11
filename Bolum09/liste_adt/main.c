/* Liste ADT'yi yalniz arayuz uzerinden kullanan program: basa bes deger
 * ekler, 2. konumdaki ogeyi siler; uzunluk, silinen deger ve 20'nin
 * konumu yazilir. Gerceklemenin (liste.c) degismesi bu dosyayi etkilemez.
 * Slayt: "Liste ADT Sozlesmesi" (kullanan program ders notundan). */
#include <stdio.h>
#include "liste.h"                      // yalnız arayüz

int main(void) {
    Liste *L = liste_olustur();
    int x, k;
    if (L == NULL) return 1;
    for (k = 1; k <= 5; k++)
        liste_ekle(L, 0, 10 * k);       // hep başa: 50 40 30 20 10
    liste_sil(L, 2, &x);                // 30 çıkar
    printf("%d %d %d\n", liste_uzunluk(L), x, liste_ara(L, 20));
    liste_yok_et(L);
    return 0;
}

/* Beklenen cikti:
 * 4 30 2
 */
