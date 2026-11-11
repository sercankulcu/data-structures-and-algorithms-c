/* Kullanilabilir dugum listesi (avail): get_node once avail'den alir,
 * yoksa malloc'a gider; ret_node free yerine dugumu avail'in basina koyar.
 * d_iade dairesel bir listeyi dongusuz, O(1)'de avail'e iade eder.
 * Notlardaki ornek: sekiz dugumlu avail'den uc dugum alinip 3 -> 5 -> 8
 * dairesel listesi kurulur; d_iade'den sonra avail 3, 5, 8 diye baslar.
 * Slaytlar: "Kullanilabilir Dugum Listesi", "Dairesel Listeyi Iade". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: dugum tipi "Dugum Yapisi" slaytindan */
typedef struct oge *oge_gost;
struct oge {
    int deger;
    oge_gost bag;
};

oge_gost avail = NULL;        // kullanılabilir düğümler

oge_gost get_node(void) {
    oge_gost p;
    if (avail != NULL) {         // önce listeden al
        p = avail;
        avail = avail->bag;
    } else {                     // yoksa sistemden iste
        p = malloc(sizeof *p);
        if (p == NULL) exit(1);
    }
    return p;
}

void ret_node(oge_gost p) {      // free yerine
    p->bag = avail;
    avail = p;
}

// dairesel listeyi O(1)'de avail'e iade et
void d_iade(oge_gost *son) {
    oge_gost ilk;
    if (*son != NULL) {
        ilk = (*son)->bag;     // ilk düğüm
        (*son)->bag = avail;   // halkayı aç
        avail = ilk;
        *son = NULL;
    }
}

/* sunumda yok: avail zincirinin uzunlugu */
static int avail_uzunluk(void) {
    int n = 0;
    for (oge_gost p = avail; p != NULL; p = p->bag) n++;
    return n;
}

int main(void)
{
    oge_gost d[8], a, b, c, son, p, q;
    int i;
    for (i = 0; i < 8; i++) d[i] = get_node();   /* avail bos: sekizi de malloc */
    for (i = 0; i < 8; i++) ret_node(d[i]);
    printf("avail: %d dugum\n", avail_uzunluk());

    a = get_node(); a->deger = 3;                /* get_node alanlari ilklendirmez */
    b = get_node(); b->deger = 5;
    c = get_node(); c->deger = 8;
    a->bag = b; b->bag = c; c->bag = a;          /* 3 -> 5 -> 8 dairesel */
    son = c;
    printf("liste kuruldu, avail: %d dugum\n", avail_uzunluk());

    d_iade(&son);
    printf("d_iade sonrasi avail: %d dugum, ilk uc: %d %d %d, son %s NULL\n",
           avail_uzunluk(), avail->deger, avail->bag->deger,
           avail->bag->bag->deger, son == NULL ? "==" : "!=");

    p = get_node();                              /* yeniden kullanim */
    ret_node(p);
    q = get_node();
    printf("iade edilen dugum geri verildi: %s\n", q == p ? "evet" : "hayir");
    ret_node(q);

    while (avail != NULL) {                      /* sunumda yok: sisteme iade */
        p = avail;
        avail = avail->bag;
        free(p);
    }
    return 0;
}

/* Beklenen cikti:
 * avail: 8 dugum
 * liste kuruldu, avail: 5 dugum
 * d_iade sonrasi avail: 8 dugum, ilk uc: 3 5 8, son == NULL
 * iade edilen dugum geri verildi: evet
 */
