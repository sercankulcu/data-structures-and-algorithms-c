/* Bagli liste ile yigin: top liste basidir. push yeni dugumu eski ustun
 * onune baglar; pop once degeri ve bagi kurtarir, en son free eder;
 * yigit_temizle kalan dugumleri iade eder.
 * Notlardaki ornekler: bos yigina 10, 20, 30 itilip dort kez pop; sonra
 * push 10, 20, 30, pop, push 40 ve yigit_temizle.
 * Slaytlar: "Bagli push Adim Adim", "Bagli pop Adim Adim",
 * "Isaretciler ve Bellek". */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dugum {
    int deger;
    struct dugum *bag;
} dugum;

void yigit_temizle(dugum **top) {
    while (*top != NULL) {
        dugum *eski = *top;
        *top = eski->bag;
        free(eski);
    }
}                  /* sonunda *top == NULL */

bool push(dugum **top, int x) {
  dugum *yeni = malloc(sizeof *yeni);
  if (yeni == NULL) return false;  /* bellek yok */
  yeni->deger = x;
  yeni->bag = *top;      /* eski üstü göster */
  *top = yeni;           /* yeni üst */
  return true;
}

bool pop(dugum **top, int *x) {
  dugum *eski = *top;      /* malloc yok! */
  if (eski == NULL) return false;  /* boş */
  *x = eski->deger;
  *top = eski->bag;        /* üstü ilerlet */
  free(eski);              /* belleği bırak */
  return true;
}

/* sunumda yok: yigini ustten alta yazar */
static void yaz(const dugum *top) {
    printf("yigin:");
    for (; top != NULL; top = top->bag) printf(" %d ->", top->deger);
    printf(" NULL\n");
}

int main(void)
{
    dugum *top = NULL;
    int x, i;
    push(&top, 10);
    push(&top, 20);
    push(&top, 30);
    yaz(top);
    for (i = 0; i < 4; i++) {
        if (pop(&top, &x)) printf("pop: true, %d\n", x);
        else printf("pop: false (bos)\n");
    }

    push(&top, 10);
    push(&top, 20);
    push(&top, 30);
    pop(&top, &x);
    push(&top, 40);
    yaz(top);
    yigit_temizle(&top);
    printf("yigit_temizle sonrasi top %s NULL\n", top == NULL ? "==" : "!=");
    return 0;
}

/* Beklenen cikti:
 * yigin: 30 -> 20 -> 10 -> NULL
 * pop: true, 30
 * pop: true, 20
 * pop: true, 10
 * pop: false (bos)
 * yigin: 40 -> 20 -> 10 -> NULL
 * yigit_temizle sonrasi top == NULL
 */
