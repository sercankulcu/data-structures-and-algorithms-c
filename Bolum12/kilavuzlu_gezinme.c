/* Kilavuzlu ikili agacta yiginsiz gezinme: kok ortada ardil bulma,
 * baslik dugumunden baslayip basliga donene dek ardildan ardila gecen
 * kok ortada gezinme ve kok onde ardil bulma. Agac sola_ekle ve saga_ekle
 * ile kurulur.
 * Notlardaki ana ornek (Ornek 12.1): A(B(D(H, I), E), C(F, G));
 * kok ortada H D I B E A F C G, kok onde A B D H I E C F G.
 * Slaytlar: "Kilavuz Bayraklari", "Ardil Bulma", "Kilavuzlu Gezinme Adim
 * Adim", "Kok Onde Kilavuzlu Gezinme", "saga_ekle() Adim Adim",
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

kilavuz_gost kokonde_ardil_bul(kilavuz_gost p) {
  if (!p->solKilavuz)        // sol çocuk varsa o
    return p->solCocuk;
  while (p->sagKilavuz)      // sağ kılavuzlarla çık
    p = p->sagCocuk;
  return p->sagCocuk;        // ilk gerçek sağ çocuk
}

/* sunumda yok: kok onde gezinme, kilavuz_kokortada_dolas'in benzeri */
static void kilavuz_kokonde_dolas(kilavuz_gost L) {
    kilavuz_gost p = L;
    for (;;) {
        p = kokonde_ardil_bul(p);
        if (p == L) break;
        printf("%c ", p->veri);
    }
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

int main(void)
{
    kilavuz_gost L = bos_kilavuzlu_agac();
    printf("bos agac, kok ortada: ");
    kilavuz_kokortada_dolas(L);          /* hicbir sey yazmaz */
    printf("\n");

    /* A(B(D(H, I), E), C(F, G)) */
    kilavuz_gost d[9];
    const char *ad = "ABCDEFGHI";
    for (int i = 0; i < 9; i++)
        d[i] = kilavuz_dugum(ad[i]);
    kilavuz_gost A = d[0], B = d[1], C = d[2], D = d[3], E = d[4],
                 F = d[5], G = d[6], H = d[7], I = d[8];
    sola_ekle(L, A);                     /* ilk dugum: baslik solunda */
    sola_ekle(A, B);  saga_ekle(A, C);
    sola_ekle(B, D);  saga_ekle(B, E);
    sola_ekle(C, F);  saga_ekle(C, G);
    sola_ekle(D, H);  saga_ekle(D, I);

    printf("ardil(baslik) = %c\n", kokortada_ardil_bul(L)->veri);
    printf("ardil(A) = %c, ardil(I) = %c\n",
           kokortada_ardil_bul(A)->veri, kokortada_ardil_bul(I)->veri);
    printf("ardil(G) baslik mi: %s\n",
           kokortada_ardil_bul(G) == L ? "evet" : "hayir");

    printf("kok ortada: ");
    kilavuz_kokortada_dolas(L);
    printf("\nkok onde: ");
    kilavuz_kokonde_dolas(L);
    printf("\nkok ortada tersten: ");
    kilavuz_tersten_dolas(L);
    printf("\n");

    kilavuzlu_agac_sil(L);
    return 0;
}

/* Not: ilk satir ve uc gezinme satiri birer boslukla biter. */
/* Beklenen cikti:
 * bos agac, kok ortada:
 * ardil(baslik) = H
 * ardil(A) = F, ardil(I) = B
 * ardil(G) baslik mi: evet
 * kok ortada: H D I B E A F C G
 * kok onde: A B D H I E C F G
 * kok ortada tersten: G C F A E B I D H
 */
