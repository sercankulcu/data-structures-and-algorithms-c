/* Dizi ile dogrusal kuyruk: on ilk ogenin bir oncesini, arka son ogeyi
 * gosterir; iki indis de yalniz ileri gider. kuyruk_ekle arka'yi, kuyruk_al
 * on'u adresle alir. Dolu/bos durumunda uyari yazilir ve program biter.
 * Notlardaki izleme: A, B, C eklenir; iki oge alinir; D eklenir. Notlarda
 * MAX_QUEUE_SIZE = 4 iken E eklenmek istenince iki hucre bos oldugu halde
 * "Kuyruk Dolu!!!" cikar (sahte doluluk); o adim burada calistirilmaz,
 * yalniz on ve arka'nin hep ileri gittigi gosterilir.
 * Slaytlar: "Dizi ile Dogrusal Kuyruk", "Dogrusal Kuyruk Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

/* sunumda yok: oge tipi ve hata fonksiyonlari (notlardan) */
typedef struct {
    int deger;
} element;
void kuyruk_dolu(void) {
    printf("Kuyruk Dolu!!!\n"); exit(-1);
}
void kuyruk_bos(void) {
    printf("Kuyruk Bos!!!\n"); exit(-2);
}

#define MAX_QUEUE_SIZE 100
element kuyruk[MAX_QUEUE_SIZE];
int on = -1;        /* ilk öğenin bir öncesi */
int arka = -1;      /* son öğe */

void kuyruk_ekle(int *arka, element item) {
    if (*arka >= MAX_QUEUE_SIZE - 1)   /* yer var mı? */
        kuyruk_dolu();         /* uyar ve çık */
    kuyruk[++*arka] = item;    /* önce artır, sonra yaz */
}
element kuyruk_al(int *on, int arka) {
    if (*on == arka)
        kuyruk_bos();          /* boşsa uyar ve çık */
    return kuyruk[++*on];      /* artır ve öndekini döndür */
}

/* sunumda yok: indisleri ve kuyrugu (on+1 .. arka) yazar */
static void durum(void) {
    printf("on = %d, arka = %d, kuyruk:", on, arka);
    for (int i = on + 1; i <= arka; i++) printf(" %c", kuyruk[i].deger);
    printf("\n");
}

int main(void)
{
    element e;
    const char *harf = "ABC";
    durum();
    for (int i = 0; i < 3; i++) {
        e.deger = harf[i];
        kuyruk_ekle(&arka, e);
    }
    durum();
    e = kuyruk_al(&on, arka);
    printf("al -> %c\n", e.deger);
    e = kuyruk_al(&on, arka);
    printf("al -> %c\n", e.deger);
    durum();
    e.deger = 'D';
    kuyruk_ekle(&arka, e);
    durum();
    printf("hucre 0..%d artik kullanilamaz, kalan yer: %d\n",
           on, MAX_QUEUE_SIZE - 1 - arka);
    return 0;
}

/* Beklenen cikti:
 * on = -1, arka = -1, kuyruk:
 * on = -1, arka = 2, kuyruk: A B C
 * al -> A
 * al -> B
 * on = 1, arka = 2, kuyruk: C
 * on = 1, arka = 3, kuyruk: C D
 * hucre 0..1 artik kullanilamaz, kalan yer: 96
 */
