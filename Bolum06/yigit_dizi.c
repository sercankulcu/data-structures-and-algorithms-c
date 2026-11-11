/* Kuresel dizi uzerinde yigin: top cagiranda yerel bir degiskendir ve
 * adresle verilir. yigit_ekle once top'u artirir sonra yazar
 * (yigit[++*top]); yigit_al once okur sonra azaltir (yigit[(*top)--]).
 * Dolu/bos durumunda uyari yazilir ve program biter.
 * Notlardaki izleme: A, B, C eklenir, bir oge alinir, sonra D ve E eklenir.
 * (Notlarda MAX_STACK_SIZE = 4 ile F'nin eklenmesi "Yigit dolu!!!" ile
 * programi bitirir; burada o adim calistirilmaz.)
 * Slaytlar: "Yigin: C Tanimlari", "yigit_ekle ve yigit_al",
 * "yigit_ekle / yigit_al Adim Adim". */
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 101

typedef struct {
    int deger;
    /* diğer alanlar */
} element;

element yigit[MAX_STACK_SIZE];

void yigit_dolu(void) {
    printf("Yigit dolu!!!\n"); exit(-1);
}
void yigit_bos(void) {
    printf("Yigit bos!!!\n"); exit(-2);
}

void yigit_ekle(int *top, element item) {
    if (*top >= MAX_STACK_SIZE - 1)  /* yer var mı? */
        yigit_dolu();         /* uyar ve çık */
    yigit[++*top] = item;     /* önce işaretçiyi artır */
}                             /* sonra öğeyi yerleştir */

element yigit_al(int *top) {
    if (*top < 0)
        yigit_bos();          /* boşsa uyar ve çık */
    return yigit[(*top)--];   /* döndür, sonra azalt */
}

/* sunumda yok: top'u ve yigit[0..top]'u yazar */
static void durum(int top) {
    printf("top = %d, yigit:", top);
    for (int i = 0; i <= top; i++) printf(" %c", yigit[i].deger);
    printf("\n");
}

int main(void)
{
    int top = -1;                    /* bos yigin */
    element e;
    char harf[] = "ABC";
    printf("basla: ");
    durum(top);
    for (int i = 0; i < 3; i++) {
        e.deger = harf[i];
        yigit_ekle(&top, e);
        printf("ekle %c: ", harf[i]);
        durum(top);
    }
    e = yigit_al(&top);
    printf("al -> %c: ", e.deger);
    durum(top);
    e.deger = 'D'; yigit_ekle(&top, e);
    printf("ekle D: ");
    durum(top);
    e.deger = 'E'; yigit_ekle(&top, e);
    printf("ekle E: ");
    durum(top);
    while (top >= 0) {               /* sunumda yok: yigini bosalt */
        e = yigit_al(&top);
        printf("al -> %c\n", e.deger);
    }
    return 0;
}

/* Beklenen cikti:
 * basla: top = -1, yigit:
 * ekle A: top = 0, yigit: A
 * ekle B: top = 1, yigit: A B
 * ekle C: top = 2, yigit: A B C
 * al -> C: top = 1, yigit: A B
 * ekle D: top = 2, yigit: A B D
 * ekle E: top = 3, yigit: A B D E
 * al -> E
 * al -> D
 * al -> B
 * al -> A
 */
