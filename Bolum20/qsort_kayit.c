/* qsort ile kayit (struct) siralama: ada_gore alfabetik, nota_gore_azalan
 * yuksek notu one alir. Ornek, notlardaki bes ogrenci. qsort kararli degildir:
 * nota_gore_azalan esit notlu ogrencilerin sirasini kitapliga gore degistirebilir,
 * bu yuzden o siralamadan sonra yalniz notlar yazilir. Notlardaki nota_sonra_ada
 * esitlikte ada bakar ve sonucu her kitaplikta ayni yapar.
 * Slayt: "qsort ile Kayit Siralama". */
#include <stdio.h>   /* sunumda yok */
#include <stdlib.h>  /* sunumda yok: qsort */
#include <string.h>  /* sunumda yok: strcmp */

typedef struct { char ad[20]; int not_; } ogrenci;

int ada_gore(const void *p, const void *q) {
    const ogrenci *x = p, *y = q;
    return strcmp(x->ad, y->ad);        // alfabetik
}
int nota_gore_azalan(const void *p, const void *q) {
    const ogrenci *x = p, *y = q;
    return (y->not_ > x->not_) - (y->not_ < x->not_);
}
/* qsort(s, n, sizeof s[0], ada_gore); */

/* sunumda yok: ders notundaki ikincil anahtarli karsilastirma */
int nota_sonra_ada(const void *p, const void *q) {
    const ogrenci *x = p, *y = q;
    int k = (y->not_ > x->not_) - (y->not_ < x->not_);
    if (k != 0) return k;               /* notlar farklı: yüksek not önce */
    return strcmp(x->ad, y->ad);        /* notlar eşit: alfabetik */
}

int main(void) {   /* sunumda yok */
    ogrenci s[] = {
        {"Zeynep", 85}, {"Ali", 70}, {"Mehmet", 85}, {"Ayse", 92}, {"Can", 70}
    };
    size_t n = sizeof s / sizeof s[0];

    qsort(s, n, sizeof s[0], ada_gore);
    printf("ada_gore:");
    for (size_t i = 0; i < n; i++) printf(" %s %d", s[i].ad, s[i].not_);
    printf("\n");

    qsort(s, n, sizeof s[0], nota_gore_azalan);
    printf("nota_gore_azalan (notlar):");
    for (size_t i = 0; i < n; i++) printf(" %d", s[i].not_);
    printf("\n");

    qsort(s, n, sizeof s[0], nota_sonra_ada);
    printf("nota_sonra_ada:");
    for (size_t i = 0; i < n; i++) printf(" %s %d", s[i].ad, s[i].not_);
    printf("\n");
    return 0;
}

/* Beklenen cikti:
 * ada_gore: Ali 70 Ayse 92 Can 70 Mehmet 85 Zeynep 85
 * nota_gore_azalan (notlar): 92 85 85 70 70
 * nota_sonra_ada: Ayse 92 Mehmet 85 Zeynep 85 Ali 70 Can 70
 */
