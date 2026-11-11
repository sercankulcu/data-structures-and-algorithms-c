/* Yapi dizisinde gezinme: ogrencilerin not ortalamalarinin ortalamasi.
 * Slayt: "sinif_ort() Adim Adim". Ornek nottan: Ada 3.2, Can 2.6, Ece 3.5
 * -> 3.10. */
#include <stdio.h>

typedef struct {
  int no;
  char ad[16];
  double ort;
} Ogrenci;

double sinif_ort(const Ogrenci s[], int n) {
  double top = 0.0;
  int i;
  for (i = 0; i < n; i++)
    top += s[i].ort;               /* . ile alan */
  return n > 0 ? top / n : 0.0;    /* boş sınıf */
}

int main(void) {  /* sunumda yok */
  Ogrenci s[] = {
    {101, "Ada", 3.2},
    {102, "Can", 2.6},
    {103, "Ece", 3.5},
  };
  printf("%.2f\n", sinif_ort(s, 3));
  printf("%.2f\n", sinif_ort(s, 0));   /* bos sinif */
  return 0;
}

/* Beklenen cikti:
 * 3.10
 * 0.00
 */
