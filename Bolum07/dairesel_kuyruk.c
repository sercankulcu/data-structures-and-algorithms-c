/* Dairesel kuyruk: indisler % MAX_QUEUE_SIZE ile ilerler ve sona gelince
 * basa sarar. on ilk ogenin bir oncesidir; on == arka bos demektir, bu
 * yuzden bir hucre hep bos kalir. Bu surum dolu/bos durumunda uyari yazip
 * programi bitirir.
 * Notlardaki ornek: alti hucreli kuyruga A..E eklenir, A alinir, F
 * eklenir; F sarmayla 0 numarali hucreye yazilir.
 * Slayt: "Dairesel Kuyruk Kodu". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: boyut (notlardaki ornek), oge tipi ve hata fonksiyonlari */
#define MAX_QUEUE_SIZE 6
typedef struct {
    int deger;
} element;
element kuyruk[MAX_QUEUE_SIZE];
void kuyruk_dolu(void) {
    printf("Kuyruk Dolu!!!\n"); exit(-1);
}
void kuyruk_bos(void) {
    printf("Kuyruk Bos!!!\n"); exit(-2);
}

void kuyruk_ekle(int on, int *arka, element item) {
    *arka = (*arka + 1) % MAX_QUEUE_SIZE; /* ilerlet */
    if (on == *arka) kuyruk_dolu();       /* dolu mu? */
    kuyruk[*arka] = item;                 /* yerleştir */
}
element kuyruk_al(int *on, int arka) {
    if (*on == arka) kuyruk_bos();        /* boş mu? */
    *on = (*on + 1) % MAX_QUEUE_SIZE;     /* ilerlet */
    return kuyruk[*on];                   /* döndür */
}

/* sunumda yok: indisleri ve kuyrugu ondan arkaya yazar */
static void durum(int on, int arka) {
    printf("on = %d, arka = %d, kuyruk:", on, arka);
    for (int i = on; i != arka; ) {
        i = (i + 1) % MAX_QUEUE_SIZE;
        printf(" %c@%d", kuyruk[i].deger, i);
    }
    printf("\n");
}

int main(void)
{
    int on = 0, arka = 0;              /* bos kuyruk */
    element e;
    const char *harf = "ABCDE";
    durum(on, arka);
    for (int i = 0; i < 5; i++) {
        e.deger = harf[i];
        kuyruk_ekle(on, &arka, e);
    }
    durum(on, arka);
    e = kuyruk_al(&on, arka);
    printf("al -> %c\n", e.deger);
    durum(on, arka);
    e.deger = 'F';
    kuyruk_ekle(on, &arka, e);         /* arka 5 -> 0: sarma */
    durum(on, arka);
    return 0;
}

/* Beklenen cikti:
 * on = 0, arka = 0, kuyruk:
 * on = 0, arka = 5, kuyruk: A@1 B@2 C@3 D@4 E@5
 * al -> A
 * on = 1, arka = 5, kuyruk: B@2 C@3 D@4 E@5
 * on = 1, arka = 0, kuyruk: B@2 C@3 D@4 E@5 F@0
 */
