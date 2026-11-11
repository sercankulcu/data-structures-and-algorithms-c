/* Floyd'un kaplumbaga-tavsan yontemiyle listede dongu aramak.
 * Notlardaki ornek: 1 -> 2 -> 3 -> 4 -> 5 ve 5'in bagi yanlislikla 3'u
 * gosterir; iki isaretci 3. turda 4'te bulusur. Ayni liste dongusuz
 * (5'in bagi NULL) iken sonuc false olur.
 * Slayt: "Floyd Adim Adim". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

bool dongu_var(oge_gost bas) {
    oge_gost yavas = bas, hizli = bas;
    while (hizli != NULL && hizli->bag != NULL) {
        yavas = yavas->bag;         // 1 adım
        hizli = hizli->bag->bag;    // 2 adım
        if (yavas == hizli) return true;
    }
    return false;
}

/* sunumda yok: diziden liste kurar (sona ekleyerek) */
static oge_gost liste_kur(const int a[], int n) {
    oge_gost bas = NULL, *son = &bas;
    for (int i = 0; i < n; i++) {
        oge_gost p = malloc(sizeof *p);
        if (p == NULL) exit(1);
        p->deger = a[i];
        p->bag = NULL;
        *son = p;
        son = &p->bag;
    }
    return bas;
}

/* sunumda yok: listeyi bellege iade eder */
static void liste_bosalt(oge_gost *list) {
    while (*list != NULL) {
        oge_gost p = *list;
        *list = p->bag;
        free(p);
    }
}

int main(void)
{
    int a[] = {1, 2, 3, 4, 5};
    oge_gost liste = liste_kur(a, 5);
    oge_gost uc = liste->bag->bag;            /* 3 */
    oge_gost bes = uc->bag->bag;              /* 5 */

    printf("dongusuz: %s\n", dongu_var(liste) ? "true" : "false");
    bes->bag = uc;                            /* 5 -> 3: dongu */
    printf("5 -> 3 dongulu: %s\n", dongu_var(liste) ? "true" : "false");
    bes->bag = NULL;                          /* donguyu kir, sonra bosalt */
    liste_bosalt(&liste);
    return 0;
}

/* Beklenen cikti:
 * dongusuz: false
 * 5 -> 3 dongulu: true
 */
