/* Dizgi hash'i: polinom (Horner) hash'i her adimda mod alir; djb2
 * (Bernstein) mod almadan h * 33 + c hesaplar ve tasmaya birakir.
 * unsigned long Windows'ta 32, Linux'ta 64 bittir; ciktinin her yerde ayni
 * olmasi icin djb2 sonucunun alt 32 biti yazdirilir.
 * Notlardaki ornekler: dizgi_hash("kedi", 11) = 3 (Tablo 14.5); anagramlar
 * "abc"/"cba", "ab"/"ba" (Tablo 14.4); djb2("kedi") alt 32 bit 2090432258.
 * Slaytlar: "Dizgi hash'i" (iki slayt), "Izleme: dizgi_hash". */
#include <stdio.h>

unsigned dizgi_hash(const char *s, unsigned m) {
  unsigned h = 0;
  for (; *s != '\0'; s++)
    h = (h * 31 + (unsigned char)*s) % m;
  return h;
}

unsigned long djb2(const char *s) {  /* Bernstein */
  unsigned long h = 5381;
  int c;
  while ((c = (unsigned char)*s++) != 0)
    h = h * 33 + c;
  return h;       /* sonra: h % m */
}

int main(void)
{
    const char *d[] = {"kedi", "abc", "cba", "ab", "ba"};
    for (int i = 0; i < 5; i++)
        printf("dizgi_hash(\"%s\", 11) = %u\n", d[i], dizgi_hash(d[i], 11));
    printf("djb2(\"ab\") = %lu\n", djb2("ab"));
    printf("djb2(\"abc\") = %lu\n", djb2("abc"));
    printf("djb2(\"kedi\") alt 32 bit = %lu\n", djb2("kedi") & 0xFFFFFFFFUL);
    return 0;
}

/* Beklenen cikti:
 * dizgi_hash("kedi", 11) = 3
 * dizgi_hash("abc", 11) = 5
 * dizgi_hash("cba", 11) = 0
 * dizgi_hash("ab", 11) = 3
 * dizgi_hash("ba", 11) = 0
 * djb2("ab") = 5863208
 * djb2("abc") = 193485963
 * djb2("kedi") alt 32 bit = 2090432258
 */
