/* Kilavuzlu agaca dugum ekleme. Durum 1: ebeveynin sag alt agaci yok,
 * sunumdaki alti atama yeter. Durum 2: ebeveynin sag alt agaci var;
 * saga_ekle cocugun sag bayragini ebeveynden alir ve ardilin sol kilavuzunu
 * cocuga cevirir. sola_ekle bunun aynasidir. Ters gezinme sol
 * kilavuzlarin da dogru oldugunu gosterir.
 * Notlardaki ornekler: A(-, B(C, -)) agacinda D, B'nin sagina (Durum 1);
 * A(-, B(C, D(E, F))) agacinda saga_ekle(B, X) (Durum 2);
 * A(B(D, E), C) agacinda sola_ekle(A, X) (Ornek 12.3).
 * Slaytlar: "Ekleme Girift", "Durum 1 Adim Adim", "saga_ekle() Adim Adim",
 * "Sola Ekleme Cozumu". */
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } boolean;   /* sunumda yok: TRUE/FALSE */

typedef struct kilavuz_agac *kilavuz_gost;
struct kilavuz_agac {
    short int    solKilavuz; /* TRUE: solCocuk kılavuz */
    kilavuz_gost solCocuk;
    char         veri;
    kilavuz_gost sagCocuk;
    short int    sagKilavuz; /* TRUE: sagCocuk kılavuz */
};

/* sunumda yok: dugum ayirma ve bos agac (ders notundaki yardimcilar) */
kilavuz_gost kilavuz_dugum(char veri) {
    kilavuz_gost d = malloc(sizeof *d);
    if (d == NULL) {           // bellek kalmadı
        fprintf(stderr, "bellek yok\n");
        exit(EXIT_FAILURE);
    }
    d->veri = veri;
    d->solCocuk = d->sagCocuk = NULL;   // ekleme yordamı dolduracak
    d->solKilavuz = d->sagKilavuz = TRUE;
    return d;
}
kilavuz_gost bos_kilavuzlu_agac(void) {
    kilavuz_gost L = kilavuz_dugum('-');  // başlık: verisi kullanılmaz
    L->solCocuk = L;  L->solKilavuz = TRUE;   // ağaç boş
    L->sagCocuk = L;  L->sagKilavuz = FALSE;  // sağı hep kendisi
    return L;
}

/* sunumda yok: "Ardil Bulma" ve "Kilavuzlu Gezinme" slaytlarindaki
   yordamlar */
kilavuz_gost kokortada_ardil_bul(kilavuz_gost L) {
  // L ile işaret edilen (NULL olmayan) öğenin ardılı
  kilavuz_gost p = L->sagCocuk;
  if (!L->sagKilavuz)        // sağ alt ağaç var mı
    while (!p->solKilavuz)   // en soluna dek in
      p = p->solCocuk;
  return p;
}

void kilavuz_kokortada_dolas(kilavuz_gost L) {
  kilavuz_gost p = L;        // L: başlık düğümü
  for (;;) {
    p = kokortada_ardil_bul(p);
    if (p == L) break;       // başlığa dönüldü mü
    printf("%c ", p->veri);
  }
}

/* sunumda yok: "Ekleme Girift" / "Durum 1 Adim Adim" slaytlarindaki alti
   atamayi saran yordam basligi; yalniz baba'nin sag alt agaci yokken dogru */
static void durum1_ekle(kilavuz_gost baba, kilavuz_gost cocuk) {
cocuk->sagCocuk  = baba->sagCocuk;
cocuk->sagKilavuz = TRUE;  // ebeveynin sağı yoktu
cocuk->solCocuk  = baba;
cocuk->solKilavuz = TRUE;
baba->sagCocuk   = cocuk;
baba->sagKilavuz = FALSE;  // TRUE idi
}

void saga_ekle(kilavuz_gost baba,
               kilavuz_gost cocuk) {
  // cocuk'u baba'nın sağ çocuğu yapar (kılavuzlu)
  kilavuz_gost p;
  cocuk->sagCocuk   = baba->sagCocuk;
  cocuk->sagKilavuz = baba->sagKilavuz;
  cocuk->solCocuk   = baba;
  cocuk->solKilavuz = TRUE;
  baba->sagCocuk    = cocuk;
  baba->sagKilavuz  = FALSE;
  if (!cocuk->sagKilavuz) { // ebeveynin alt ağacı var mı
    p = kokortada_ardil_bul(cocuk);
    p->solCocuk = cocuk;     // ardılın öncülü çocuk
  }
}

kilavuz_gost kokortada_oncel_bul(kilavuz_gost L) {
  kilavuz_gost p = L->solCocuk;
  if (!L->solKilavuz)
    while (!p->sagKilavuz) p = p->sagCocuk;
  return p;
}
void sola_ekle(kilavuz_gost baba, kilavuz_gost cocuk) {
  cocuk->solCocuk   = baba->solCocuk;
  cocuk->solKilavuz = baba->solKilavuz;
  cocuk->sagCocuk   = baba;
  cocuk->sagKilavuz = TRUE;      // ardılı ebeveyn
  baba->solCocuk    = cocuk;
  baba->solKilavuz  = FALSE;
  if (!cocuk->solKilavuz) {      // baba'nın sol alt ağacı vardı
    kilavuz_gost p = kokortada_oncel_bul(cocuk);
    p->sagCocuk = cocuk;         // öncülün ardılı çocuk
  }
}

/* sunumda yok: kok ortada tersten gezinme (oncelden oncele) */
static void kilavuz_tersten_dolas(kilavuz_gost L) {
    kilavuz_gost p = L;
    for (;;) {
        p = kokortada_oncel_bul(p);
        if (p == L) break;
        printf("%c ", p->veri);
    }
}

/* sunumda yok: agaci geri verir (ders notundaki yordam) */
void kilavuzlu_agac_sil(kilavuz_gost L) {
    kilavuz_gost p = kokortada_ardil_bul(L), sonraki;
    while (p != L) {
        sonraki = kokortada_ardil_bul(p);  // önce ardıl bulunur
        free(p);                           // sonra düğüm geri verilir
        p = sonraki;
    }
    free(L);                               // en son başlık
}

/* sunumda yok: iki yonde gezinip yazar */
static void yaz(const char *baslik, kilavuz_gost L) {
    printf("%s\n  kok ortada: ", baslik);
    kilavuz_kokortada_dolas(L);
    printf("\n  tersten:    ");
    kilavuz_tersten_dolas(L);
    printf("\n");
}

/* sunumda yok: bir kilavuzun gosterdigi dugumun adi */
static char ad(kilavuz_gost p, kilavuz_gost baslik) {
    return p == baslik ? '^' : p->veri;   /* ^ = baslik */
}

int main(void)
{
    /* Durum 1: A(-, B(C, -)), D B'nin sagina */
    kilavuz_gost L = bos_kilavuzlu_agac();
    kilavuz_gost A = kilavuz_dugum('A'), B = kilavuz_dugum('B'),
                 C = kilavuz_dugum('C'), D = kilavuz_dugum('D');
    sola_ekle(L, A);
    saga_ekle(A, B);
    sola_ekle(B, C);
    durum1_ekle(B, D);
    yaz("Durum 1: D, B'nin sagina (alti atama)", L);
    printf("  D: sol kilavuz -> %c, sag kilavuz -> %c\n",
           ad(D->solCocuk, L), ad(D->sagCocuk, L));
    kilavuzlu_agac_sil(L);

    /* Durum 2: A(-, B(C, D(E, F))), saga_ekle(B, X) */
    L = bos_kilavuzlu_agac();
    A = kilavuz_dugum('A');  B = kilavuz_dugum('B');
    C = kilavuz_dugum('C');  D = kilavuz_dugum('D');
    kilavuz_gost E = kilavuz_dugum('E'), F = kilavuz_dugum('F'),
                 X = kilavuz_dugum('X');
    sola_ekle(L, A);
    saga_ekle(A, B);
    sola_ekle(B, C);
    saga_ekle(B, D);
    sola_ekle(D, E);
    saga_ekle(D, F);
    printf("Durum 2 oncesi E: sol kilavuz -> %c\n", ad(E->solCocuk, L));
    saga_ekle(B, X);
    yaz("Durum 2: saga_ekle(B, X)", L);
    printf("  X: sol kilavuz -> %c, sag cocuk -> %c; E: sol kilavuz -> %c\n",
           ad(X->solCocuk, L), ad(X->sagCocuk, L), ad(E->solCocuk, L));
    kilavuzlu_agac_sil(L);

    /* Ornek 12.3: A(B(D, E), C), sola_ekle(A, X) */
    L = bos_kilavuzlu_agac();
    A = kilavuz_dugum('A');  B = kilavuz_dugum('B');
    C = kilavuz_dugum('C');  D = kilavuz_dugum('D');
    E = kilavuz_dugum('E');  X = kilavuz_dugum('X');
    sola_ekle(L, A);
    sola_ekle(A, B);
    saga_ekle(A, C);
    sola_ekle(B, D);
    saga_ekle(B, E);
    sola_ekle(A, X);
    yaz("Ornek 12.3: sola_ekle(A, X)", L);
    printf("  E: sag kilavuz -> %c\n", ad(E->sagCocuk, L));
    kilavuzlu_agac_sil(L);
    return 0;
}

/* Not: gezinme satirlari birer boslukla biter; ^ basliktir. */
/* Beklenen cikti:
 * Durum 1: D, B'nin sagina (alti atama)
 *   kok ortada: A C B D
 *   tersten:    D B C A
 *   D: sol kilavuz -> B, sag kilavuz -> ^
 * Durum 2 oncesi E: sol kilavuz -> B
 * Durum 2: saga_ekle(B, X)
 *   kok ortada: A C B X E D F
 *   tersten:    F D E X B C A
 *   X: sol kilavuz -> B, sag cocuk -> D; E: sol kilavuz -> X
 * Ornek 12.3: sola_ekle(A, X)
 *   kok ortada: D B E X A C
 *   tersten:    C A X E B D
 *   E: sag kilavuz -> X
 */
