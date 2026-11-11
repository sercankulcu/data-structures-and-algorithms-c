/* Opak yiginin kullanimi: kullanici kodu yalniz yigit.h'yi gorur.
 * Kapasitesi 3 olan yigina 1, 2, 3, 4 itilir (4 reddedilir), sonra yigin
 * bosaltilir ve yok edilir.
 * Slayt: "Arayuz ve Gercekleme". Bu dosyanin tamami sunumda yok. */
#include <stdio.h>
#include "yigit.h"

int main(void)
{
    Yigit *y = yigit_olustur(3);
    int x, i;
    if (y == NULL) return 1;
    for (i = 1; i <= 4; i++)
        printf("yigit_ekle %d: %s\n", i, yigit_ekle(y, i) ? "true" : "false");
    while (!yigit_bos(y)) {
        yigit_al(y, &x);
        printf("yigit_al: %d\n", x);
    }
    printf("yigit_al bos yiginda: %s\n", yigit_al(y, &x) ? "true" : "false");
    yigit_yok_et(y);
    return 0;
}

/* Beklenen cikti:
 * yigit_ekle 1: true
 * yigit_ekle 2: true
 * yigit_ekle 3: true
 * yigit_ekle 4: false
 * yigit_al: 3
 * yigit_al: 2
 * yigit_al: 1
 * yigit_al bos yiginda: false
 */
