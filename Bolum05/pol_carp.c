/* Polinomun bagli liste gosterimi ve carpimi. Terimler uslere gore azalan
 * sirada dugumlerde durur. YeniTerimEkle onceki dugumun pesine ekler,
 * SonrakiTerimiSil onceki dugumden sonrakini siler; yerlestir bir carpim
 * terimini yerine koyar (ayni us varsa katsayilari toplar, 0 olursa siler);
 * PolCarp her p icin aramaya bir onceki satirin basindan baslar.
 * Notlardaki ornekler: (x + 1)(x - 1) = x^2 - 1 ve (x^2 + 1)(x^2 - 1) = x^4 - 1.
 * Slaytlar: "Polinom Listesi", "Terim Ekle / Sil" (iki blok), "PolCarp Kodu",
 * "PolCarp() Adim Adim". */
#include <stdio.h>
#include <stdlib.h>

typedef struct pol_oge *pol_gosterge;
typedef struct pol_oge {
  int katsayi;
  int us;
  pol_gosterge bag;
} pol_oge;

/* terim oluştur; Onceki varsa peşine ekle */
pol_gosterge YeniTerimEkle(int Us, int Katsayi,
                           pol_gosterge Onceki) {
  pol_gosterge p = malloc(sizeof *p);
  if (!p) { printf("Bellek yetmiyor!\n"); exit(1); }
  p->us = Us;  p->katsayi = Katsayi;
  if (Onceki) {              /* araya ya da sona */
    p->bag = Onceki->bag;    /* önce yeni düğüm */
    Onceki->bag = p;         /* sonra önceki */
  } else p->bag = NULL;      /* tek başına */
  return p;
}

/* Onceki'den sonrakini sil */
void SonrakiTerimiSil(
        pol_gosterge Onceki) {
  pol_gosterge Silinecek =
        Onceki->bag;
  if (!Silinecek) return;
  Onceki->bag =
        Silinecek->bag;
  free(Silinecek);
}

pol_gosterge yerlestir(pol_gosterge r,
                       int us, int kat) {
  while (r->bag && r->bag->us > us) r = r->bag;
  if (!r->bag || r->bag->us < us)
    YeniTerimEkle(us, kat, r);         /* yeni üs */
  else if ((r->bag->katsayi += kat) == 0)
    SonrakiTerimiSil(r);               /* 0 oldu */
  return r;
}

pol_gosterge PolCarp(pol_gosterge pBas,
                     pol_gosterge qBas) {
  pol_gosterge p, q, r = NULL, bas = NULL, rBas=NULL;
  for (p = pBas; p; p = p->bag) {
    r = bas;               /* aramaya buradan başla */
    for (q = qBas; q; q = q->bag) {
      int us = p->us + q->us;
      int kat = p->katsayi * q->katsayi;
      if (rBas) r = yerlestir(r, us, kat);
      else rBas=r=bas=YeniTerimEkle(us, kat, NULL);
      if (q == qBas) bas = r;  /* sonraki p için */
    }
  }
  return rBas;
}

/* sunumda yok: polinomu yazar */
static void yaz(const char *ad, pol_gosterge p) {
  printf("%s =", ad);
  for (pol_gosterge t = p; t; t = t->bag) {
    int k = t->katsayi;
    if (t == p) printf(" %dx^%d", k, t->us);
    else printf(" %c %dx^%d", k < 0 ? '-' : '+', k < 0 ? -k : k, t->us);
  }
  printf("\n");
}

/* sunumda yok: listeyi bellege iade eder */
static void pol_bosalt(pol_gosterge p) {
  while (p) {
    pol_gosterge q = p->bag;
    free(p);
    p = q;
  }
}

/* sunumda yok: iki terimli polinom kurar (us1 > us2) */
static pol_gosterge iki_terim(int k1, int u1, int k2, int u2) {
  pol_gosterge bas = YeniTerimEkle(u1, k1, NULL);
  YeniTerimEkle(u2, k2, bas);
  return bas;
}

int main(void)
{
  pol_gosterge A = iki_terim(1, 1, 1, 0);     /* x + 1 */
  pol_gosterge B = iki_terim(1, 1, -1, 0);    /* x - 1 */
  pol_gosterge C = iki_terim(1, 2, 1, 0);     /* x^2 + 1 */
  pol_gosterge D = iki_terim(1, 2, -1, 0);    /* x^2 - 1 */
  pol_gosterge AB, CD;

  yaz("A", A);
  yaz("B", B);
  AB = PolCarp(A, B);
  yaz("A*B", AB);
  yaz("C", C);
  yaz("D", D);
  CD = PolCarp(C, D);
  yaz("C*D", CD);

  pol_bosalt(A); pol_bosalt(B); pol_bosalt(C); pol_bosalt(D);
  pol_bosalt(AB); pol_bosalt(CD);
  return 0;
}

/* Beklenen cikti:
 * A = 1x^1 + 1x^0
 * B = 1x^1 - 1x^0
 * A*B = 1x^2 - 1x^0
 * C = 1x^2 + 1x^0
 * D = 1x^2 - 1x^0
 * C*D = 1x^4 - 1x^0
 */
