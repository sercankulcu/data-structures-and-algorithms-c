/* Isaretci hatirlatmasi: bir int'i isaretciyle degistirmek, tek bir dugumu
 * malloc ile ayirip -> ile doldurmak ve free ile iade etmek.
 * Slaytlar: "Isaretci Hatirlatmasi", "Dugum Yapisi". */
#include <stdio.h>
#include <stdlib.h>

typedef struct oge *oge_gost;  // önce işaretçi türü

struct oge {
    int deger;       // veri alanı
    oge_gost bag;    // sonraki düğümün adresi
};

int main(void)
{
    oge_gost liste = NULL;  // boş liste
    int x = 5;
    int *p = &x;       // p, x'in adresini tutar
    *p = 7;            // p'nin gösterdiğine yaz: x == 7
    printf("x = %d\n", x);                         /* sunumda yok */

    oge_gost q = NULL; // henüz hiçbir düğüm yok
    q = malloc(sizeof *q);
    if (q != NULL) {
        q->deger = 3;  // (*q).deger = 3
        q->bag = NULL;
        printf("q->deger = %d, (*q).deger = %d, q->bag %s NULL\n",  /* sunumda yok */
               q->deger, (*q).deger, q->bag == NULL ? "==" : "!=");
    }
    free(q);           // iade; q artık sarkan işaretçi
    q = NULL;
    printf("liste %s NULL, q %s NULL\n",           /* sunumda yok */
           liste == NULL ? "==" : "!=", q == NULL ? "==" : "!=");
    return 0;
}

/* Beklenen cikti:
 * x = 7
 * q->deger = 3, (*q).deger = 3, q->bag == NULL
 * liste == NULL, q == NULL
 */
