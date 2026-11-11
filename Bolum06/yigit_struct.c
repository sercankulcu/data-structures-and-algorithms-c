/* Kuresel dizi yerine struct ile yigin: dizi ve ust indisi bir Yigit
 * yapisinda; tasma ve alt tasma programi bitirmez, false doner. Uygulama
 * olarak bir dizgiyi yiginla ters cevirmek.
 * Notlardaki ornekler: 5, 8, 2, 9 itilir ve dort pop yapilir (notlarda
 * KAP = 3 alindigi icin 9 reddedilir; burada KAP = 100 oldugu icin tasma
 * yigin doldurularak ayrica gosterilir); ters_cevir("YIGIT") = "TIGIY".
 * Slaytlar: "Kuresel Dizi Yerine struct", "push / pop (struct) Adim Adim",
 * "Ters Cevirme Adim Adim". */
#include <stdio.h>
#include <stdbool.h>
#define KAP 100

typedef struct {
    int veri[KAP];
    int ust;               /* boşken -1 */
} Yigit;

void yigit_baslat(Yigit *y) { y->ust = -1; }
bool yigit_bos(const Yigit *y)  { return y->ust < 0; }
bool yigit_dolu(const Yigit *y) { return y->ust == KAP - 1; }
int  yigit_boyut(const Yigit *y) { return y->ust + 1; }
bool yigit_ust(const Yigit *y, int *x) {
    if (yigit_bos(y)) return false;
    *x = y->veri[y->ust];  return true;
}

bool push(Yigit *y, int x) {
  if (y->ust == KAP - 1) return false; /* taşma */
  y->veri[++y->ust] = x;
  return true;
}
bool pop(Yigit *y, int *x) {
  if (y->ust < 0) return false;   /* alt taşma */
  *x = y->veri[y->ust--];
  return true;
}

void ters_cevir(char *s) {
  Yigit y;  int c, i;
  yigit_baslat(&y);
  for (i = 0; s[i] != '\0'; i++)
    push(&y, s[i]);     /* KAP yeterli varsayıldı */
  for (i = 0; pop(&y, &c); i++)
    s[i] = (char)c;
}

int main(void)
{
    Yigit y;
    int x, i, girdi[] = {5, 8, 2, 9};
    char s[] = "YIGIT";

    yigit_baslat(&y);
    for (i = 0; i < 4; i++) {
        bool ok = push(&y, girdi[i]);
        printf("push %d: %s, boyut %d\n", girdi[i], ok ? "true" : "false",
               yigit_boyut(&y));
    }
    if (yigit_ust(&y, &x)) printf("ust = %d\n", x);
    for (i = 0; i < 5; i++) {
        if (pop(&y, &x)) printf("pop: true, x = %d\n", x);
        else printf("pop: false (alt tasma)\n");
    }
    printf("bos: %s\n", yigit_bos(&y) ? "evet" : "hayir");

    for (i = 0; push(&y, i); i++)       /* doluncaya kadar it */
        ;
    printf("%d push basarili, dolu: %s, boyut %d\n", i,
           yigit_dolu(&y) ? "evet" : "hayir", yigit_boyut(&y));

    ters_cevir(s);
    printf("ters_cevir(\"YIGIT\") = \"%s\"\n", s);
    return 0;
}

/* Beklenen cikti:
 * push 5: true, boyut 1
 * push 8: true, boyut 2
 * push 2: true, boyut 3
 * push 9: true, boyut 4
 * ust = 9
 * pop: true, x = 9
 * pop: true, x = 2
 * pop: true, x = 8
 * pop: true, x = 5
 * pop: false (alt tasma)
 * bos: evet
 * 100 push basarili, dolu: evet, boyut 100
 * ters_cevir("YIGIT") = "TIGIY"
 */
