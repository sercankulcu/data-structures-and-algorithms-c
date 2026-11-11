/* Kesir ADT'sinin arayuzu: opak tip ve islemlerin bildirimleri.
 * Slayt: "C'de Soyutlama: Baslik Dosyasi". */
/* kesir.h : arayuz (NE?) */
#ifndef KESIR_H
#define KESIR_H
typedef struct kesir Kesir; /* opak */

Kesir *kesir_olustur(int pay, int payda);
Kesir *kesir_topla(const Kesir *a,
                   const Kesir *b);
int  kesir_esit(const Kesir *a,
                const Kesir *b);
void kesir_yaz(const Kesir *k);
void kesir_sil(Kesir *k);
#endif
