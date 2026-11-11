/* Basamak siralamasi (radixsort, LSD): her oge uc basamagini tutan bir bagli
 * liste dugumudur. Birler, onlar, yuzler basamagi icin sirayla on kovaya
 * kararli dagitilir ve kovalar 0'dan 9'a toplanir. Sunumdaki dongu govdesi
 * notlardaki gibi radixsort fonksiyonu olarak yazildi; liste_kur ve liste_sil
 * notlardandir. Ornek, notlardaki 179, 208, 306, 093, 859, 984, 055, 009,
 * 271, 033.
 * Slaytlar: "Cok Anahtarli Siralama", "radixsort(): Birler Gecisi",
 * "radixsort(): Onlar ve Yuzler". */
#include <stdio.h>   /* sunumda yok */
#include <stdlib.h>  /* sunumda yok: malloc, free */

#define MAX_DIGIT 3
#define RADIX 10
typedef struct oge *oge_gost;
struct oge {
    int deger[MAX_DIGIT];  /* 179 → {1, 7, 9} */
    oge_gost bag;
};

/* sunumda yok: fonksiyon basi ve kova dizileri ders notundan */
oge_gost radixsort(oge_gost p) {
    oge_gost on[RADIX], arka[RADIX];  /* kova başları ve sonları */
    for (int i = MAX_DIGIT - 1; i >= 0; i--) {
        for (int j = 0; j < RADIX; j++)
            on[j] = arka[j] = NULL;
        for (; p; p = p->bag) {     // dağıt
            int b = p->deger[i];
            if (!on[b]) on[b] = p;
            else arka[b]->bag = p;
            arka[b] = p;
        }
        for (int j = RADIX - 1; j >= 0; j--) // topla
            if (on[j]) { arka[j]->bag = p; p = on[j]; }
    }
    return p;
}

void liste_sil(oge_gost *pp);   /* sunumda yok: prototip */

/* sunumda yok: ders notundan */
/* 3 basamaklı sayılardan bağlı liste kurar; bellek yetmezse kurulanı geri verir */
oge_gost liste_kur(const int x[], int n) {
    oge_gost bas = NULL, son = NULL;
    for (int k = 0; k < n; k++) {
        oge_gost d = malloc(sizeof *d);
        if (d == NULL) {               /* yarıda kaldı: sızıntı olmasın */
            liste_sil(&bas);
            return NULL;
        }
        d->deger[0] = x[k] / 100;      /* yüzler */
        d->deger[1] = x[k] / 10 % 10;  /* onlar */
        d->deger[2] = x[k] % 10;       /* birler */
        d->bag = NULL;
        if (son) son->bag = d; else bas = d;
        son = d;
    }
    return bas;
}

/* sunumda yok: ders notundan */
/* listenin bütün düğümlerini geri verir ve çağıranın işaretçisini NULL yapar */
void liste_sil(oge_gost *pp) {
    while (*pp) {
        oge_gost sonraki = (*pp)->bag;
        free(*pp);
        *pp = sonraki;
    }
}

/* sunumda yok: listeyi uc basamakla yazdirir */
static void yazdir(const char *ad, oge_gost p) {
    printf("%s", ad);
    for (; p; p = p->bag)
        printf(" %d%d%d", p->deger[0], p->deger[1], p->deger[2]);
    printf("\n");
}

int main(void) {   /* sunumda yok */
    int x[] = {179, 208, 306, 93, 859, 984, 55, 9, 271, 33};
    oge_gost p = liste_kur(x, 10);
    if (p == NULL) return 1;
    yazdir("once: ", p);
    p = radixsort(p);
    yazdir("sonra:", p);
    liste_sil(&p);
    return 0;
}

/* Beklenen cikti:
 * once:  179 208 306 093 859 984 055 009 271 033
 * sonra: 009 033 055 093 179 208 271 306 859 984
 */
