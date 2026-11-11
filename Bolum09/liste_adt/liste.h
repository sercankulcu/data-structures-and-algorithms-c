/* Liste ADT arayuzu: opak Liste tipi ve sozlesmesi yazili islemler.
 * Slayt: "Liste ADT Sozlesmesi". */
#ifndef LISTE_H   /* sunumda yok: baslik korumasi */
#define LISTE_H

#include <stdbool.h>  /* sunumda yok: bool */

typedef struct liste Liste;           // opak tür

Liste *liste_olustur(void);
void   liste_yok_et(Liste *L);
int    liste_uzunluk(const Liste *L);
bool   liste_getir(const Liste *L, int i, int *x);
bool   liste_ekle(Liste *L, int i, int x);  // 0<=i<=n
bool   liste_sil(Liste *L, int i, int *x);  // 0<=i<n
int    liste_ara(const Liste *L, int x);    // yoksa -1

#endif
