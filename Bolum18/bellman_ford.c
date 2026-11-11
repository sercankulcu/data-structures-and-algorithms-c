/* Bellman-Ford: butun kenarlar n - 1 tur gevsetilir; n. turda hala gevseyen
 * kenar varsa erisilebilir negatif dongu vardir (-1). O(n e).
 * Notlardaki ornekler: 0->1 (4), 0->2 (5), 1->3 (2), 2->1 (-3): d = 0 2 5 4;
 * toplami -1 olan 1 -> 2 -> 1 dongusunde sonuc -1.
 * Slayt: "Bellman-Ford Adim Adim" (yordam basligi ders notundan). */
#include <stdio.h>

#define SONSUZ 1000      /* sunumda yok: bolumdeki "baglanti yok" sabiti */

/* sunumda yok: ders notundaki kenar listesi ve yordam basligi */
typedef struct {
    int u, v, w;        /* kenar <u,v>, agirlik w */
} kenar;
int BellmanFord(kenar K[], int n, int e, int s, int d[])
{
    int i, j, t, u, v;
    for (i = 0; i < n; i++) d[i] = SONSUZ;
    d[s] = 0;
    for (t = 1; t <= n - 1; t++)          /* n-1 tur */
        for (j = 0; j < e; j++) {
            u = K[j].u;  v = K[j].v;
            if (d[u] != SONSUZ && d[u] + K[j].w < d[v])
                d[v] = d[u] + K[j].w;
        }
    for (j = 0; j < e; j++)               /* n. tur */
        if (d[K[j].u] != SONSUZ &&
            d[K[j].u] + K[j].w < d[K[j].v]) return -1;
    return 0;              /* -1: negatif dongu var */
}

int main(void)
{
    kenar K1[] = { {0, 1, 4}, {0, 2, 5}, {1, 3, 2}, {2, 1, -3} };
    kenar K2[] = { {0, 1, 1}, {1, 2, 2}, {2, 1, -3} };
    int d[4], i, r;

    r = BellmanFord(K1, 4, 4, 0, d);
    printf("ornek: sonuc = %d, d =", r);
    for (i = 0; i < 4; i++) printf(" %d", d[i]);
    printf("\n");

    r = BellmanFord(K2, 3, 3, 0, d);
    printf("negatif dongu: sonuc = %d\n", r);
    return 0;
}

/* Beklenen cikti:
 * ornek: sonuc = 0, d = 0 2 5 4
 * negatif dongu: sonuc = -1
 */
