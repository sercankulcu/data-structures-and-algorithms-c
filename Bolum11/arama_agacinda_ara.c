/* Ikili arama agacinda arama: yinelemeli arama_agacinda_ara, ozyinelemeli
 * ara, sunumdaki "calisir mi?" govdesi (arama) ve siralama bilgisini
 * kullanmayan ara_ozyineli. Notlardaki ornekler: 47, 55, 49, 26, 34, 17,
 * 52, 84, 93 agacinda 52, 34 ve 60 aranir; kok 5, solu 9 (9'un sagi 1),
 * sagi 2 olan genel agacta 2, 1 ve 7 aranir.
 * Slaytlar: "arama_agacinda_ara() Adim Adim", "ara() Ozyinelemeli Adim
 * Adim", "Ozyinelemeli Aramada Tuzak", "Ornek Cozum: Genel Arama". */
#include <stdio.h>
#include <stdlib.h>

typedef enum { FALSE, TRUE } boolean;
typedef struct dugum *agac_gost;
struct dugum {
    agac_gost solcocuk;
    int       veri;
    agac_gost sagcocuk;
};

/* sunumda yok: ogeal'in govdesi (ders notundaki gerceklemesi) */
agac_gost ogeal(void) {
    agac_gost r = malloc(sizeof *r);
    if (!r) {
        fprintf(stderr, "Bellek yetersiz\n");
        exit(EXIT_FAILURE);
    }
    r->solcocuk = r->sagcocuk = NULL;
    return r;
}

/* sunumda yok: agaci kurmak icin "arama_agacina_ekle() Adim Adim"
   slaytindaki yordam */
boolean arama_agacina_ekle(int x, agac_gost *L) {
  agac_gost q = NULL, p = *L, r; // q arka, p ön
  while (p) {                    // NULL'a dek in
    q = p;                       // arkayı günle
    if (x < p->veri) p = p->solcocuk;
    else if (x > p->veri) p = p->sagcocuk;
    else { printf("Benzer deger var.\n");
           return FALSE; }
  }
  r = ogeal();                   // çocuklar NULL
  r->veri = x;
  if (*L == NULL) *L = r;        // boş ağaç: kök
  else if (x < q->veri) q->solcocuk = r;
  else q->sagcocuk = r;
  return TRUE;
}

agac_gost arama_agacinda_ara(int x, agac_gost L) {
  while (L) {           // uygun alt ağaçta in
    if (x == L->veri) return L;
    if (x < L->veri) L = L->solcocuk;
    else             L = L->sagcocuk;
  }
  return NULL;          // bulunamadı
}

agac_gost ara(int x, agac_gost L) {
  if (!L) return NULL;          // yok
  if (x == L->veri) return L;   // bulundu
  if (x < L->veri)
    return ara(x, L->solcocuk);
  return ara(x, L->sagcocuk);
}

/* sunumda yok: "Ozyinelemeli Aramada Tuzak" slaytindaki govdeyi saran
   yordam basligi */
agac_gost arama(int x, agac_gost L) {
if (L) {
  if (x == L->veri) return L;
  if (x <  L->veri) return arama(x, L->solcocuk);
  return arama(x, L->sagcocuk);
}
return NULL;   /* L == NULL: boş (alt) ağaç */
}

agac_gost ara_ozyineli(int veri, agac_gost L) {
  if (!L) return NULL;              /* ağaç boş mu   */
  if (L->veri == veri) return L;    /* aranan bulundu */
  agac_gost T = ara_ozyineli(veri, L->solcocuk);
  return T ? T : ara_ozyineli(veri, L->sagcocuk);
}

/* sunumda yok: arama sonucunu yazar */
static void sonuc(const char *ad, int x, agac_gost p) {
    if (p) printf("%s(%d): bulundu, veri = %d\n", ad, x, p->veri);
    else   printf("%s(%d): yok\n", ad, x);
}

/* sunumda yok: tek dugum ayirir */
static agac_gost dugum_yap(int x) {
    agac_gost r = ogeal();
    r->veri = x;
    return r;
}

/* sunumda yok: agaci bellege iade eder (kok sonda) */
static void agac_sil(agac_gost L) {
    if (L) {
        agac_sil(L->solcocuk);
        agac_sil(L->sagcocuk);
        free(L);
    }
}

int main(void)
{
    int sira[] = {47, 55, 49, 26, 34, 17, 52, 84, 93};
    agac_gost L = NULL;
    for (int i = 0; i < 9; i++)
        arama_agacina_ekle(sira[i], &L);

    printf("Ikili arama agaci:\n");
    sonuc("arama_agacinda_ara", 52, arama_agacinda_ara(52, L));
    sonuc("arama_agacinda_ara", 60, arama_agacinda_ara(60, L));
    sonuc("ara", 34, ara(34, L));
    sonuc("ara", 60, ara(60, L));
    sonuc("arama", 34, arama(34, L));
    sonuc("ara_ozyineli", 84, ara_ozyineli(84, L));

    /* genel ikili agac: 5(9(-, 1), 2) */
    agac_gost G = dugum_yap(5);
    G->solcocuk = dugum_yap(9);
    G->solcocuk->sagcocuk = dugum_yap(1);
    G->sagcocuk = dugum_yap(2);

    printf("Genel ikili agac:\n");
    sonuc("arama", 2, arama(2, G));    /* sola gider, 2'yi kacirir */
    sonuc("ara_ozyineli", 2, ara_ozyineli(2, G));
    sonuc("ara_ozyineli", 1, ara_ozyineli(1, G));
    sonuc("ara_ozyineli", 7, ara_ozyineli(7, G));

    agac_sil(L);
    agac_sil(G);
    return 0;
}

/* Beklenen cikti:
 * Ikili arama agaci:
 * arama_agacinda_ara(52): bulundu, veri = 52
 * arama_agacinda_ara(60): yok
 * ara(34): bulundu, veri = 34
 * ara(60): yok
 * arama(34): bulundu, veri = 34
 * ara_ozyineli(84): bulundu, veri = 84
 * Genel ikili agac:
 * arama(2): yok
 * ara_ozyineli(2): bulundu, veri = 2
 * ara_ozyineli(1): bulundu, veri = 1
 * ara_ozyineli(7): yok
 */
