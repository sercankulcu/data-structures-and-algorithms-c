/* yigit.h: opak yigin arayuzu. Kullanici struct Yigit'in alanlarini
 * gormez, yalniz isaretciyle calisir.
 * Slayt: "Arayuz ve Gercekleme" (1. blok). */
/* yigit.h: kullanıcı yalnız bunu görür */
#ifndef YIGIT_H
#define YIGIT_H
#include <stdbool.h>
typedef struct Yigit Yigit;  /* opak */
Yigit *yigit_olustur(int kapasite);
void yigit_yok_et(Yigit *y);
bool yigit_ekle(Yigit *y, int x);
bool yigit_al(Yigit *y, int *x);
bool yigit_bos(const Yigit *y);
#endif
