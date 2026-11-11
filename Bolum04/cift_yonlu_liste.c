/* Baslikli dairesel cift yonlu bagli liste: p'nin sagina ekleme
 * (cift_ekle) ve aramasiz O(1) silme (cift_sil). Her adimda degismez
 * p == p->sol->sag == p->sag->sol denetlenir.
 * Notlardaki ornek: H <-> 4 <-> 8 <-> H listesinde 4'un sagina 6; sonra
 * 6, 4 ve 8 silinir, en sonda basligi silme denemesi reddedilir.
 * Slaytlar: "Cift Yonlu Bagli Liste", "Cift Yonlu Bagli Ekleme Adim Adim",
 * "Cift Yonlu Baglida Silme". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct doge *doge_gost;
struct doge {
    doge_gost sol;   // önceki (llink)
    int deger;
    doge_gost sag;   // sonraki (rlink)
};
// değişmez: p == p->sol->sag == p->sag->sol

// p düğümünün sağına yeni düğümü ekler
void cift_ekle(doge_gost p, doge_gost yeni) {
    yeni->sol = p;
    yeni->sag = p->sag;
    p->sag->sol = yeni;
    p->sag = yeni;
}

void cift_sil(doge_gost baslik, doge_gost p) {
    if (p == baslik) {       // başlık silinmez
        fprintf(stderr, "Baslik silinemez\n");
        return;
    }
    p->sol->sag = p->sag;
    p->sag->sol = p->sol;
    free(p);
}

/* sunumda yok: dugum ayirir */
static doge_gost yeni_doge(int x) {
    doge_gost p = malloc(sizeof *p);
    if (p == NULL) exit(1);
    p->sol = p->sag = p;
    p->deger = x;
    return p;
}

/* sunumda yok: ileri ve geri yazdirir, degismezi denetler */
static void yazdir(doge_gost H) {
    doge_gost p;
    bool tamam = true;
    printf("ileri: H");
    for (p = H->sag; p != H; p = p->sag)
        printf(" %d", p->deger);
    printf(" | geri: H");
    for (p = H->sol; p != H; p = p->sol)
        printf(" %d", p->deger);
    p = H;
    do {
        if (p->sol->sag != p || p->sag->sol != p) tamam = false;
        p = p->sag;
    } while (p != H);
    printf(" | degismez %s\n", tamam ? "saglandi" : "BOZUK");
}

int main(void)
{
    doge_gost H = yeni_doge(0);      /* bos liste: iki bag da kendini gosterir */
    doge_gost d4 = yeni_doge(4), d6 = yeni_doge(6), d8 = yeni_doge(8);
    yazdir(H);
    cift_ekle(H, d4);
    cift_ekle(d4, d8);
    yazdir(H);
    cift_ekle(d4, d6);               /* 4'un sagina 6 */
    yazdir(H);
    cift_sil(H, d6);
    yazdir(H);
    cift_sil(H, d4);                 /* ilk gercek dugum */
    yazdir(H);
    cift_sil(H, d8);                 /* son gercek dugum */
    yazdir(H);
    printf("H->sol == H: %s, H->sag == H: %s\n",
           H->sol == H ? "evet" : "hayir", H->sag == H ? "evet" : "hayir");
    fflush(stdout);                  /* sunumda yok: stderr satiri sirayla ciksin */
    cift_sil(H, H);                  /* reddedilir */
    free(H);                         /* sunumda yok */
    return 0;
}

/* Not: cift_sil(H, H) stderr'e "Baslik silinemez" yazar; asagida yalniz stdout var. */
/* Beklenen cikti:
 * ileri: H | geri: H | degismez saglandi
 * ileri: H 4 8 | geri: H 8 4 | degismez saglandi
 * ileri: H 4 6 8 | geri: H 8 6 4 | degismez saglandi
 * ileri: H 4 8 | geri: H 8 4 | degismez saglandi
 * ileri: H 8 | geri: H 8 | degismez saglandi
 * ileri: H | geri: H | degismez saglandi
 * H->sol == H: evet, H->sag == H: evet
 */
